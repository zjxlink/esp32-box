/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


#include "custom.h"
#include "app_wifi.h"
static void screen_wifi_btn_connect_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
        char ssid[32];
        lv_dropdown_get_selected_str(guider_ui.screen_wifi_ddlist_ssid, ssid, sizeof(ssid));
        const char * passwd = lv_textarea_get_text(guider_ui.screen_wifi_ta_pwd);
        wifi_reconnect_sta_figure(ssid, passwd);
		break;
	}
	default:
		break;
	}
}
static void screen_wifi_btn_rescan_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		app_network_rescan();
		break;
	}
	default:
		break;
	}
}
void events_init_screen_wifi(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_wifi_btn_connect, screen_wifi_btn_connect_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_wifi_btn_rescan, screen_wifi_btn_rescan_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{

}
