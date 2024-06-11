
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "mbedtls/md.h"
#include "mbedtls/sha256.h"
#include "mbedtls/base64.h"
#include "app_asr.h"
#include "esp_heap_caps.h"
#include "esp_check.h"
#include "esp_err.h"
#include "cJSON.h"
#include "esp_crt_bundle.h"

#define SPIRAM_SIZE (2 * 1024 * 1024)
#define RESPONSE_SPIRAM_SIZE (10 * 1024)

static const char *TAG = "ASR";

typedef struct {
    uint8_t *buffer;
    int buffer_size;
} ASR_Data;

static ASR_Data asr_data;

static uint8_t *encoded_audio_buffer;
static char *payload_buffer;
static char *response_buffer;

static void get_utc_date(int64_t timestamp, char *utc, int len) {
    struct tm sttime;
    gmtime_r(&timestamp, &sttime);
    strftime(utc, len, "%Y-%m-%d", &sttime);
}

static void asr_sha256_hex(const char *str, char *output) {
    unsigned char hash[32];
    mbedtls_sha256_context sha256_ctx;
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, 0);
    mbedtls_sha256_update(&sha256_ctx, (const unsigned char *)str, strlen(str));
    mbedtls_sha256_finish(&sha256_ctx, hash);
    mbedtls_sha256_free(&sha256_ctx);

    for (int i = 0; i < 32; ++i) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
}

static void asr_hmac_sha256(const unsigned char *key, int key_len, const unsigned char *input, int input_len, unsigned char *output) {
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
    mbedtls_md_hmac_starts(&ctx, key, key_len);
    mbedtls_md_hmac_update(&ctx, input, input_len);
    mbedtls_md_hmac_finish(&ctx, output);
    mbedtls_md_free(&ctx);
}

static void asr_hex_encode(const unsigned char *input, int len, char *output) {
    for (int i = 0; i < len; ++i) {
        sprintf(output + (i * 2), "%02x", input[i]);
    }
}

static esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
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
            if (!esp_http_client_is_chunked_response(evt->client)) {
                snprintf(response_buffer, RESPONSE_SPIRAM_SIZE, "%s", (char *)evt->data);
                response_buffer[evt->data_len] = 0;
                printf("%.*s", evt->data_len, (char *)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
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

static char* get_result_value(const char *json_string) {
    char *result_value = NULL;

    cJSON *json = cJSON_Parse(json_string);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            ESP_LOGE(TAG, "Error before: %s", error_ptr);
        } else {
            ESP_LOGE(TAG, "Unknown error while parsing JSON.");
        }
        return result_value;
    }

    cJSON *response = cJSON_GetObjectItemCaseSensitive(json, "Response");
    if (response == NULL || !cJSON_IsObject(response)) {
        ESP_LOGE(TAG, "Response object not found in JSON.");
        cJSON_Delete(json);
        return result_value;
    }

    cJSON *result = cJSON_GetObjectItemCaseSensitive(response, "Result");
    if (result == NULL || !cJSON_IsString(result)) {
        ESP_LOGE(TAG, "Result string not found in Response.");
        cJSON_Delete(json);
        return result_value;
    }

    // Allocate memory for the result value and copy the string
    result_value = strdup(result->valuestring);
    if (result_value == NULL) {
        ESP_LOGE(TAG, "Memory allocation failed.");
        cJSON_Delete(json);
        return result_value;
    }

    cJSON_Delete(json);
    return result_value;
}

char* req_asr(uint8_t *audio_buffer, size_t audio_buffer_len) 
{
    if(NULL == encoded_audio_buffer) {
        encoded_audio_buffer = (uint8_t *)heap_caps_malloc(SPIRAM_SIZE, MALLOC_CAP_SPIRAM);
        if (encoded_audio_buffer == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for encoded_audio_buffer");
            return NULL;
        }
    }

    if(NULL == payload_buffer) {
        payload_buffer = (char *)heap_caps_malloc(SPIRAM_SIZE, MALLOC_CAP_SPIRAM);
        if (payload_buffer == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for payload_buffer");
            return NULL;
        }
    }
    
    if(NULL == response_buffer) {
        response_buffer = (char *)heap_caps_malloc(RESPONSE_SPIRAM_SIZE, MALLOC_CAP_SPIRAM);
        if (response_buffer == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for response_buffer");
            return NULL;
        }
    }


    
    
    const char *TOKEN = "";

    const char *service = "asr";
    const char *host = "asr.tencentcloudapi.com";
    const char *region = "";
    const char *action = "SentenceRecognition";
    const char *action_lower = "sentencerecognition";
    const char *version = "2019-06-14";

    int64_t timestamp = time(NULL);
    char date[20] = {0};
    get_utc_date(timestamp, date, sizeof(date));

    // Base64 encode audio buffer
    size_t output_len;
    
    mbedtls_base64_encode(encoded_audio_buffer, SPIRAM_SIZE, &output_len, audio_buffer, audio_buffer_len);
    encoded_audio_buffer[output_len] = '\0'; // Null-terminate the encoded string

    char tmp = encoded_audio_buffer[100]; // Null-terminate the encoded string
    encoded_audio_buffer[100] = '\0';
    ESP_LOGD(TAG, "Step 1, encoded_audio_buffer=%s, len=%d", encoded_audio_buffer, output_len);
    encoded_audio_buffer[100] = tmp; // Null-terminate the encoded string

    // Step 1: Build canonical request
    const char *http_request_method = "POST";
    const char *canonical_uri = "/";
    const char *canonical_query_string = "";
    char canonical_headers[256];
    snprintf(canonical_headers, 256, "content-type:application/json\nhost:%s\nx-tc-action:%s\n", host, action_lower);
    const char *signed_headers = "content-type;host;x-tc-action";

    // Create JSON payload_buffer
    snprintf(payload_buffer, SPIRAM_SIZE, "{\"EngSerViceType\":\"16k_zh\",\"SourceType\":1,\"VoiceFormat\":\"pcm\",\"Data\":\"%s\"}", encoded_audio_buffer);

    char hashed_request_payload_buffer[65] = {0};
    asr_sha256_hex(payload_buffer, hashed_request_payload_buffer);

    char canonical_request[512];
    snprintf(canonical_request, 512, "%s\n%s\n%s\n%s\n%s\n%s", http_request_method, canonical_uri, canonical_query_string, canonical_headers, signed_headers, hashed_request_payload_buffer);

    ESP_LOGD(TAG, "Step 2, canonical_request=%s", canonical_request);
    // Step 2: Build string to sign
    const char *algorithm = "TC3-HMAC-SHA256";
    char request_timestamp[32];
    snprintf(request_timestamp, sizeof(request_timestamp), "%lld", timestamp);
    char credential_scope[64];
    snprintf(credential_scope, sizeof(credential_scope), "%s/%s/tc3_request", date, service);
    char hashed_canonical_request[65] = {0};
    asr_sha256_hex(canonical_request, hashed_canonical_request);
    char string_to_sign[512];

    snprintf(string_to_sign, 512, "%s\n%s\n%s\n%s", algorithm, request_timestamp, credential_scope, hashed_canonical_request);

    ESP_LOGD(TAG, "Step 3, string_to_sign=%s", string_to_sign);
    // Step 3: Calculate signature
    char k_key[64];
    snprintf(k_key, sizeof(k_key), "TC3%s", SECRET_KEY);
    unsigned char k_date[32];
    asr_hmac_sha256((unsigned char *)k_key, strlen(k_key), (unsigned char *)date, strlen(date), k_date);
    unsigned char k_service[32];
    asr_hmac_sha256(k_date, 32, (unsigned char *)service, strlen(service), k_service);
    unsigned char k_signing[32];
    asr_hmac_sha256(k_service, 32, (unsigned char *)"tc3_request", strlen("tc3_request"), k_signing);
    unsigned char k_hmac_sha_sign[32];
    asr_hmac_sha256(k_signing, 32, (unsigned char *)string_to_sign, strlen(string_to_sign), k_hmac_sha_sign);

    char signature[65];
    asr_hex_encode(k_hmac_sha_sign, 32, signature);

    ESP_LOGD(TAG, "Step 4");
    // Step 4: Build Authorization header
    char authorization[512];

    snprintf(authorization, 512, "%s Credential=%s/%s, SignedHeaders=%s, Signature=%s",
             algorithm, SECRET_ID, credential_scope, signed_headers, signature);

    ESP_LOGD(TAG, "Step 5, authorization=%s", authorization);
    // Step 5: Make the HTTP request
    esp_http_client_config_t config = {
        .url = "https://asr.ap-chongqing.tencentcloudapi.com",
        .event_handler = _http_event_handler,
        .crt_bundle_attach = esp_crt_bundle_attach,
    };

        esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Authorization", authorization);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_header(client, "Host", host);
    esp_http_client_set_header(client, "X-TC-Action", action);
    esp_http_client_set_header(client, "X-TC-Timestamp", request_timestamp);
    esp_http_client_set_header(client, "X-TC-Version", version);
    esp_http_client_set_header(client, "X-TC-Region", region);
    esp_http_client_set_header(client, "X-TC-Token", TOKEN);
    esp_http_client_set_post_field(client, payload_buffer, strlen(payload_buffer));

    ESP_LOGD(TAG, "Step 6");
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTPS Status = %d, content_length = %d",
                 (int)esp_http_client_get_status_code(client),
                 (int)esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        return NULL;
    }
    ESP_LOGD(TAG, "Step 7");
    esp_http_client_cleanup(client);

    char *result_value = get_result_value(response_buffer);
    if (result_value != NULL) {
        return result_value;
    } 

    return NULL;
}