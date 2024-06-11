#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "esp_crt_bundle.h"

#define OPENROUTER_URL "https://openrouter.ai/api/v1/chat/completions"
#define OPENROUTER_API_KEY "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"

static const char *TAG = "OpenAI";

#define RESPONSE_BUFFER_SIZE (100 * 1024)

const char *Model_Lists[64] = {
    "openchat/openchat-7b:free",
    "openrouter/auto",
    "mistralai/mistral-7b-instruct",
    "mistralai/mixtral-8x7b-instruct",
    "gryphe/mythomax-l2-13b",
    "openai/gpt-3.5-turbo"
};

#define     OPENROUTER_MODEL_FREE1          0
#define     OPENROUTER_MODEL_AUTO           1
#define     OPENROUTER_MODEL_MIS7B          2
#define     OPENROUTER_MODEL_MIS8X7B        3
#define     OPENROUTER_MODEL_MYTHOMAX       4
#define     OPENROUTER_MODEL_OPENAI35       5

#define OPENROUTER_MODEL Model_Lists[OPENROUTER_MODEL_OPENAI35]

static char *openai_answer;
static char *assistant;
static char *response_buffer = NULL;
static int response_buffer_len = 0;

static char* extract_json_data(char* buffer, int length) {
    int start_index = -1, end_index = -1;
    
    // Search for the first opening curly brace '{'
    for (int i = 0; i < length; i++) {
        if (buffer[i] == '{') {
            start_index = i;
            break;
        }
    }

    // If opening curly brace is not found, return NULL
    if (start_index == -1) {
        ESP_LOGE(TAG, "Opening curly brace not found");
        return NULL;
    }

    // Search for the last closing curly brace '}' starting from the end of the buffer
    for (int i = length - 1; i >= 0; i--) {
        if (buffer[i] == '}') {
            end_index = i;
            break;
        }
    }

    // If closing curly brace is not found, return NULL
    if (end_index == -1) {
        ESP_LOGE(TAG, "Closing curly brace not found");
        return NULL;
    }

    // Allocate memory for the JSON data
    int json_length = end_index - start_index + 1;

    // Copy JSON data from buffer to json_data
    buffer[end_index+1] = '\0';  // Null-terminate the string

    return &buffer[start_index];
}

static char* extract_content(const char* response_raw) {

    if(response_raw == NULL || strlen(response_raw)==0) {
        ESP_LOGE(TAG, "extract_content, response_raw is NULL");
        return NULL;
    }

    ESP_LOGD(TAG, "response_raw=%s",response_raw);
    
    char* response = extract_json_data(response_raw, strlen(response_raw));

    if(response == NULL || strlen(response)==0) {
        ESP_LOGE(TAG, "extract_content, response is NULL");
        return NULL;
    }

    ESP_LOGD(TAG, "response=%s",response);

    cJSON *json = cJSON_Parse(response);
    if (json == NULL) {
        ESP_LOGE(TAG, "Error parsing JSON");
        return NULL;
    }

    cJSON *choices = cJSON_GetObjectItem(json, "choices");
    if (!cJSON_IsArray(choices)) {
        ESP_LOGE(TAG, "choices is not an array");
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *choice = cJSON_GetArrayItem(choices, 0);
    if (!cJSON_IsObject(choice)) {
        ESP_LOGE(TAG, "choice is not an object");
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *message = cJSON_GetObjectItem(choice, "message");
    if (!cJSON_IsObject(message)) {
        ESP_LOGE(TAG, "message is not an object");
        cJSON_Delete(json);
        return NULL;
    }

    cJSON *content = cJSON_GetObjectItem(message, "content");
    if (!cJSON_IsString(content)) {
        ESP_LOGE(TAG, "content is not a string");
        cJSON_Delete(json);
        return NULL;
    }

    char *result = strdup(content->valuestring);
    cJSON_Delete(json);
    return result;
}

static esp_err_t http_event_handler(esp_http_client_event_t *evt) {
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                // Not chunked, process normally
                printf("%.*s", evt->data_len, (char*)evt->data);
            } else {
                // Handle chunked data
                memcpy(response_buffer + response_buffer_len, evt->data, evt->data_len);
                response_buffer_len += evt->data_len;
                response_buffer[response_buffer_len] = '\0';  // Null-terminate the string
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            if (response_buffer) {
                openai_answer = extract_content(response_buffer);
                if (openai_answer) {
                    ESP_LOGD(TAG, "answer = %s", openai_answer);
                } else {
                    ESP_LOGE(TAG, "Failed to extract content");
                }
                memset(response_buffer, 0, RESPONSE_BUFFER_SIZE);
                response_buffer = NULL;
                response_buffer_len = 0;
            }
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGI(TAG, "HTTP_EVENT_REDIRECT");
            break;
        default:
            break;
    }
    return ESP_OK;
}

/* Need to free return char string */
char* start_openai(char *question) {
    esp_err_t ret = ESP_OK;

    if(NULL == response_buffer) {
        response_buffer = (char *)heap_caps_malloc(RESPONSE_BUFFER_SIZE, MALLOC_CAP_SPIRAM);
        if (response_buffer == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for response_buffer");
            return NULL;
        }
    }

    //if(NULL == assistant) {
    //    assistant = (char *)heap_caps_malloc(RESPONSE_BUFFER_SIZE, MALLOC_CAP_SPIRAM);
    //    if (assistant == NULL) {
    //        ESP_LOGE(TAG, "Failed to allocate memory for assistant");
    //        return NULL;
    //    }
    //    memset(assistant, 0, RESPONSE_BUFFER_SIZE);
    //}

    if(question == NULL || strlen(question)==0)  return NULL; 

    ESP_LOGW(TAG, "Question = %s", question);

    //openai_answer = NULL;

    // Configure HTTP client
    esp_http_client_config_t config = {
        .url = OPENROUTER_URL,
        .method = HTTP_METHOD_POST,
        .timeout_ms = 15000,
        .event_handler = http_event_handler,
        .crt_bundle_attach = esp_crt_bundle_attach,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    // Prepare the JSON payload
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "model", OPENROUTER_MODEL);

    cJSON *messages = cJSON_CreateArray();
    cJSON *system_message = cJSON_CreateObject();
    cJSON_AddStringToObject(system_message, "role", "system");
    cJSON_AddStringToObject(system_message, "content", "你现在是一个聊天助手。你会以友好和专业的方式回答用户的问题，提供建议，并进行对话。");
    cJSON_AddItemToArray(messages, system_message);

    cJSON *user_message = cJSON_CreateObject();
    cJSON_AddStringToObject(user_message, "role", "user");
    cJSON_AddStringToObject(user_message, "content", question);
    cJSON_AddItemToArray(messages, user_message);

    //cJSON *asst_message = cJSON_CreateObject();
    //cJSON_AddStringToObject(asst_message, "role", "assistant");
    //if(assistant && (strlen(assistant)!=0)) cJSON_AddStringToObject(asst_message, "content", assistant);
    //else cJSON_AddStringToObject(asst_message, "content", "你好！有什么可以帮忙的吗？");
    //cJSON_AddItemToArray(messages, asst_message);

    cJSON_AddItemToObject(root, "messages", messages);

    // Add OpenAI parameters
    cJSON_AddNumberToObject(root, "temperature", 0.7);
    cJSON_AddNumberToObject(root, "max_tokens", 1000);
    cJSON_AddNumberToObject(root, "top_p", 1.0);
    cJSON_AddNumberToObject(root, "frequency_penalty", 0.5);
    cJSON_AddNumberToObject(root, "presence_penalty", 0.6);

    char *post_data = cJSON_Print(root);

    ESP_LOGI(TAG, "post_data: %s", post_data);

    // Set POST data and headers
    esp_http_client_set_url(client, OPENROUTER_URL);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "application/json");

    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Bearer %s", OPENROUTER_API_KEY);
    esp_http_client_set_header(client, "Authorization", auth_header);

    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    // 设置内容长度头以防止chunked编码
    //char content_length_header[64];
    //snprintf(content_length_header, sizeof(content_length_header), "%d", strlen(post_data));
    //esp_http_client_set_header(client, "Content-Length", content_length_header);

    // Perform the POST request
    ret = esp_http_client_perform(client);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
                 (int)esp_http_client_get_status_code(client),
                 (int)esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(ret));
    }

    // Clean up
    esp_http_client_cleanup(client);
    cJSON_Delete(root);
    free(post_data);

    if(openai_answer) {
        ESP_LOGW(TAG, "Answer = %s", openai_answer);

        size_t str_len = strlen(openai_answer);
        for (size_t i = 0; i < str_len; i++) {
        if (openai_answer[i] == '\\' || openai_answer[i] == '\"' ||
            openai_answer[i] == '{' || openai_answer[i] == '}' ||
            openai_answer[i] == '[' || openai_answer[i] == ']' ||
            openai_answer[i] == ':' || openai_answer[i] == ',' ||
            openai_answer[i] == '\n' || openai_answer[i] == '\r' ||
            openai_answer[i] == '\t') {
            openai_answer[i] = ' ';
            }
        }
    }

    //memcpy(assistant, openai_answer, strlen(openai_answer));

    return openai_answer;
}
