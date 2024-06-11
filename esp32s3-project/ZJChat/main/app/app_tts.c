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
#include "esp_heap_caps.h"
#include "esp_check.h"
#include "esp_err.h"
#include "cJSON.h"
#include "esp_crt_bundle.h"

static const char *TAG = "TTS";

#define AUDIO_TTL_FILE "/sdcard/tts_output"


static const char *TOKEN = "";
static const char *service = "tts";
static const char *host = "tts.tencentcloudapi.com";
static const char *region = "ap-chongqing";
static const char *action = "TextToVoice";
static const char *action_lower = "texttovoice";
static const char *version = "2019-08-23";

#define RESPONSE_SPIRAM_SIZE (2 * 1024 * 1024)

static char *response_buffer;
static uint8_t *audio_buffer;
static int response_len;

static int SessionId = 0;

static void get_utc_date(int64_t timestamp, char *utc, int len) {
    struct tm sttime;
    gmtime_r(&timestamp, &sttime);
    strftime(utc, len, "%Y-%m-%d", &sttime);
}

static void sha256_hex(const char *str, char *output) {
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

static void hmac_sha256(const unsigned char *key, int key_len, const unsigned char *input, int input_len, unsigned char *output) {
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
    mbedtls_md_hmac_starts(&ctx, key, key_len);
    mbedtls_md_hmac_update(&ctx, input, input_len);
    mbedtls_md_hmac_finish(&ctx, output);
    mbedtls_md_free(&ctx);
}

static void hex_encode(const unsigned char *input, int len, char *output) {
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
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (response_len + evt->data_len < RESPONSE_SPIRAM_SIZE) {
                memcpy(response_buffer + response_len, evt->data, evt->data_len);
                response_len += evt->data_len;
            } else {
                ESP_LOGE(TAG, "Response buffer overflow");
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
            response_buffer[response_len] = 0; // Null-terminate the buffer
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

static uint8_t *base64_decode(const char *input, size_t input_len, size_t *output_len) {
    int ret = mbedtls_base64_decode(audio_buffer, input_len, output_len, (const unsigned char *)input, input_len);
    if (ret != 0) {
        ESP_LOGE(TAG, "Base64 decode failed with error code: %d", ret);
        return NULL;
    }

    return audio_buffer;
}

// 提取和解码 Audio 数据的函数
static uint8_t* extract_and_decode_audio(const char *response_buffer, size_t *audio_data_len) {
    // 解析 JSON 响应
    cJSON *json_response = cJSON_Parse(response_buffer);
    if (json_response == NULL) {
        ESP_LOGE(TAG, "JSON Parse Error");
        return NULL;
    }

    cJSON *response = cJSON_GetObjectItem(json_response, "Response");
    if (response == NULL) {
        ESP_LOGE(TAG, "JSON Response Error");
        cJSON_Delete(json_response);
        return NULL;
    }

    cJSON *audio_item = cJSON_GetObjectItem(response, "Audio");
    if (audio_item == NULL) {
        ESP_LOGE(TAG, "Audio Data Error");
        cJSON_Delete(json_response);
        return NULL;
    }

    const char *audio_base64 = audio_item->valuestring;
    uint8_t *audio_data = base64_decode(audio_base64, strlen(audio_base64), audio_data_len);

    if (audio_data == NULL) {
        ESP_LOGE(TAG, "Audio Data Decode Error");
    }

    cJSON_Delete(json_response);
    return audio_data;
}

static char* save_audio_file(const uint8_t *data, size_t data_len) {
    static char audio_filename[64];
    static int audio_index=0;
    snprintf(audio_filename, 64, "%s_%d.MP3", AUDIO_TTL_FILE, audio_index);
    FILE *file = fopen(audio_filename, "wb");
    if (file == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return NULL;
    }

    size_t written = fwrite(data, 1, data_len, file);
    if (written != data_len) {
        ESP_LOGE(TAG, "Failed to write complete data to file");
        fclose(file);
        return NULL;
    } else {
        ESP_LOGI(TAG, "Audio data written to file successfully, len=%d", written);
    }

    fclose(file);

    audio_index++;

    return audio_filename;
}

char* req_tts(const char *text) 
{
    if(NULL == response_buffer) {
        response_buffer = (char *)heap_caps_malloc(RESPONSE_SPIRAM_SIZE, MALLOC_CAP_SPIRAM);
        if (response_buffer == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for response_buffer");
            return NULL;
        }
    }
    response_len = 0;

    if(NULL == audio_buffer) {
        audio_buffer = (uint8_t *)heap_caps_malloc(RESPONSE_SPIRAM_SIZE, MALLOC_CAP_SPIRAM);
        if (audio_buffer == NULL) {
            ESP_LOGE(TAG, "Failed to allocate memory for audio_buffer");
            return NULL;
        }
    }

    int64_t timestamp = time(NULL);
    char date[20] = {0};
    get_utc_date(timestamp, date, sizeof(date));

    // Step 1: Build canonical request
    const char *http_request_method = "POST";
    const char *canonical_uri = "/";
    const char *canonical_query_string = "";
    char canonical_headers[256];
    snprintf(canonical_headers, 256, "content-type:application/json; charset=utf-8\nhost:%s\nx-tc-action:%s\n", host, action_lower);
    const char *signed_headers = "content-type;host;x-tc-action";

    // Create JSON payload
    char payload_buffer[512];
    snprintf(payload_buffer, 512, "{\"Text\":\"%s.\",\"SessionId\":\"session-%08d\",\"VoiceType\":101016,\"Codec\":\"mp3\",\"EmotionCategory\":\"happy\",\"Volume\":10}", text, SessionId);

    ESP_LOGE(TAG, "payload_buffer = %s", payload_buffer);

    char hashed_request_payload_buffer[65] = {0};
    sha256_hex(payload_buffer, hashed_request_payload_buffer);

    char canonical_request[512];
    snprintf(canonical_request, 512, "%s\n%s\n%s\n%s\n%s\n%s", http_request_method, canonical_uri, canonical_query_string, canonical_headers, signed_headers, hashed_request_payload_buffer);

    // Step 2: Build string to sign
    const char *algorithm = "TC3-HMAC-SHA256";
    char request_timestamp[32];
    snprintf(request_timestamp, sizeof(request_timestamp), "%lld", timestamp);
    char credential_scope[64];
    snprintf(credential_scope, sizeof(credential_scope), "%s/%s/tc3_request", date, service);
    char hashed_canonical_request[65] = {0};
    sha256_hex(canonical_request, hashed_canonical_request);
    char string_to_sign[512];
    snprintf(string_to_sign, 512, "%s\n%s\n%s\n%s", algorithm, request_timestamp, credential_scope, hashed_canonical_request);

    // Step 3: Calculate signature
    char k_key[64];
    snprintf(k_key, sizeof(k_key), "TC3%s", SECRET_KEY);
    unsigned char k_date[32];
    hmac_sha256((unsigned char *)k_key, strlen(k_key), (unsigned char *)date, strlen(date), k_date);
    unsigned char k_service[32];
    hmac_sha256(k_date, 32, (unsigned char *)service, strlen(service), k_service);
    unsigned char k_signing[32];
    hmac_sha256(k_service, 32, (unsigned char *)"tc3_request", strlen("tc3_request"), k_signing);
    unsigned char k_hmac_sha_sign[32];
    hmac_sha256(k_signing, 32, (unsigned char *)string_to_sign, strlen(string_to_sign), k_hmac_sha_sign);

    char signature[65];
    hex_encode(k_hmac_sha_sign, 32, signature);

    // Step 4: Build Authorization header
    char authorization[512];
    snprintf(authorization, 512, "%s Credential=%s/%s, SignedHeaders=%s, Signature=%s",
             algorithm, SECRET_ID, credential_scope, signed_headers, signature);

    // Step 5: Make the HTTP request
    esp_http_client_config_t config = {
        .url = "https://tts.tencentcloudapi.com",
        .event_handler = _http_event_handler,
        .crt_bundle_attach = esp_crt_bundle_attach,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Authorization", authorization);
    esp_http_client_set_header(client, "Content-Type", "application/json; charset=utf-8");
    esp_http_client_set_header(client, "Host", host);
    esp_http_client_set_header(client, "X-TC-Action", action);
    esp_http_client_set_header(client, "X-TC-Timestamp", request_timestamp);
    esp_http_client_set_header(client, "X-TC-Version", version);
    esp_http_client_set_header(client, "X-TC-Language", "zh-CN");
    esp_http_client_set_header(client, "X-TC-Region", region);
    esp_http_client_set_post_field(client, payload_buffer, strlen(payload_buffer));

    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTPS Status = %d, content_length = %d",
                 (int)esp_http_client_get_status_code(client),
                 (int)esp_http_client_get_content_length(client));

        size_t audio_data_len;
        uint8_t *decoded_audio = extract_and_decode_audio(response_buffer, &audio_data_len);
        if (decoded_audio == NULL) {
            ESP_LOGE(TAG, "Failed to decode base64 audio data, %s", response_buffer);
            esp_http_client_cleanup(client);
            return NULL;
        }

        char *audio_file;
        if ((audio_file = save_audio_file(decoded_audio, audio_data_len)) != NULL) {
            esp_http_client_cleanup(client);
            return audio_file;
        } else {
            ESP_LOGE(TAG, "save_audio_file failed");
            esp_http_client_cleanup(client);
            return NULL;
        }
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        return NULL;
    }

    return NULL;
}

