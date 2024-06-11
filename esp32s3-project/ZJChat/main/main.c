/*
 * @Author: Zhoujie
 * @Date: 2024-06-03 11:56:44
 * @LastEditors: Zhoujie
 * @LastEditTime: 2024-06-11 16:43:06
 * @FilePath: \ZJChat\main\main.c
 * @Description: 
 * 
 * Copyright (c) 2024 by Triloop, All Rights Reserved. 
 */

/*
 * SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_sntp.h"
#include "nvs_flash.h"
#include "audio_player.h"
#include "bsp/esp-bsp.h"
#include "bsp_board.h"
#include "app_sr.h"
#include "app_wifi.h"
#include "gui_guider.h"
#include "events_init.h"

static char *TAG = "app_main";

lv_ui guider_ui;

/* play audio function */
static void audio_play_finish_cb(void)
{
    ESP_LOGI(TAG, "replay audio end");
    
}

void time_sync_notification_cb(struct timeval *tv) {
    ESP_LOGI(TAG, "Time synchronized");
}

void initialize_sntp(void) {
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "ntp.tencent.com"); // 使用默认NTP服务器
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_init();
}

void obtain_time(void) 
{
    initialize_sntp();

    // 等待时间同步
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 20;

    while (timeinfo.tm_year < (2016 - 1900) && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
        vTaskDelay(pdMS_TO_TICKS(2000));
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    if (retry == retry_count) {
        ESP_LOGE(TAG, "Failed to get NTP time");
    } else {
        ESP_LOGI(TAG, "Time is set: %s", asctime(&timeinfo));
    }

    // 设置时区为中国标准时间（CST-8）
    setenv("TZ", "CST-8", 1);
    tzset();

    // 获取并打印当前时间
    time(&now);
    localtime_r(&now, &timeinfo);
    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
}

void app_main()
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    bsp_spiffs_mount();

    bsp_i2c_init();

    bsp_display_cfg_t cfg = {
        .lvgl_port_cfg = ESP_LVGL_PORT_INIT_CONFIG(),
        .buffer_size = BSP_LCD_H_RES * CONFIG_BSP_LCD_DRAW_BUF_HEIGHT,
        .double_buffer = 0,
        .flags = {
            .buff_dma = true,
        }
    };
    bsp_display_start_with_config(&cfg);
    bsp_board_init();

    bsp_sdcard_mount();

    ESP_LOGI(TAG, "Display LVGL demo");
    bsp_display_backlight_on();

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    ui_load_scr_animation(&guider_ui, &guider_ui.screen_wifi, guider_ui.screen_wifi_del, &guider_ui.screen_del, \
        setup_scr_screen_wifi, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
    app_network_start(&guider_ui);
    
    while(WIFI_STATUS_CONNECTED_OK != wifi_connected_already()) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    /* SNTP 对时 */
    obtain_time();

    app_sr_start(true);

    ui_load_scr_animation(&guider_ui, &guider_ui.screen_sleep, guider_ui.screen_sleep_del, &guider_ui.screen_del, \
        setup_scr_screen_sleep, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);

    while (true) {

        ESP_LOGI(TAG, "\tDescription\tInternal\tSPIRAM");
        ESP_LOGI(TAG, "Current Free Memory\t%d\t\t%d",
                 heap_caps_get_free_size(MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL),
                 heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
        ESP_LOGI(TAG, "Min. Ever Free Size\t%d\t\t%d",
                 heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT | MALLOC_CAP_INTERNAL),
                 heap_caps_get_minimum_free_size(MALLOC_CAP_SPIRAM));
        vTaskDelay(pdMS_TO_TICKS(5 * 1000));
    }
}
