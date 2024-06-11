/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_wifi(lv_ui *ui)
{
	//Write codes screen_wifi
	ui->screen_wifi = lv_obj_create(NULL);
	ui->g_kb_screen_wifi = lv_keyboard_create(ui->screen_wifi);
	lv_obj_add_event_cb(ui->g_kb_screen_wifi, kb_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(ui->g_kb_screen_wifi, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(ui->g_kb_screen_wifi, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_size(ui->screen_wifi, 320, 240);
	lv_obj_set_scrollbar_mode(ui->screen_wifi, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wifi_label_1
	ui->screen_wifi_label_1 = lv_label_create(ui->screen_wifi);
	lv_label_set_text(ui->screen_wifi_label_1, "SSID");
	lv_label_set_long_mode(ui->screen_wifi_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wifi_label_1, -19, 34);
	lv_obj_set_size(ui->screen_wifi_label_1, 100, 32);

	//Write style for screen_wifi_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wifi_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wifi_label_1, &lv_font_pingfang_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_wifi_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wifi_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wifi_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wifi_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wifi_label_2
	ui->screen_wifi_label_2 = lv_label_create(ui->screen_wifi);
	lv_label_set_text(ui->screen_wifi_label_2, "密码");
	lv_label_set_long_mode(ui->screen_wifi_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_wifi_label_2, -25, 80);
	lv_obj_set_size(ui->screen_wifi_label_2, 100, 32);

	//Write style for screen_wifi_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wifi_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wifi_label_2, &lv_font_pingfang_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_wifi_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wifi_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wifi_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wifi_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wifi_ta_pwd
	ui->screen_wifi_ta_pwd = lv_textarea_create(ui->screen_wifi);
	lv_textarea_set_text(ui->screen_wifi_ta_pwd, "");
	lv_textarea_set_placeholder_text(ui->screen_wifi_ta_pwd, "Password");
	lv_textarea_set_password_bullet(ui->screen_wifi_ta_pwd, "*");
	lv_textarea_set_password_mode(ui->screen_wifi_ta_pwd, false);
	lv_textarea_set_one_line(ui->screen_wifi_ta_pwd, false);
	lv_textarea_set_accepted_chars(ui->screen_wifi_ta_pwd, "");
	lv_textarea_set_max_length(ui->screen_wifi_ta_pwd, 32);
	#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
		lv_obj_add_event_cb(ui->screen_wifi_ta_pwd, ta_event_cb, LV_EVENT_ALL, ui->g_kb_screen_wifi);
	#endif
	lv_obj_set_pos(ui->screen_wifi_ta_pwd, 54, 75);
	lv_obj_set_size(ui->screen_wifi_ta_pwd, 180, 32);

	//Write style for screen_wifi_ta_pwd, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_wifi_ta_pwd, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wifi_ta_pwd, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_wifi_ta_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_wifi_ta_pwd, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wifi_ta_pwd, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wifi_ta_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wifi_ta_pwd, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_wifi_ta_pwd, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_wifi_ta_pwd, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_wifi_ta_pwd, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_wifi_ta_pwd, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_wifi_ta_pwd, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wifi_ta_pwd, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wifi_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wifi_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wifi_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_ta_pwd, 4, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_wifi_ta_pwd, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wifi_ta_pwd, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wifi_ta_pwd, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_wifi_ta_pwd, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_ta_pwd, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_wifi_ddlist_ssid
	ui->screen_wifi_ddlist_ssid = lv_dropdown_create(ui->screen_wifi);
	lv_dropdown_set_options(ui->screen_wifi_ddlist_ssid, "");
	lv_obj_set_pos(ui->screen_wifi_ddlist_ssid, 54, 28);
	lv_obj_set_size(ui->screen_wifi_ddlist_ssid, 180, 32);

	//Write style for screen_wifi_ddlist_ssid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_wifi_ddlist_ssid, lv_color_hex(0x0D3055), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wifi_ddlist_ssid, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_wifi_ddlist_ssid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_wifi_ddlist_ssid, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_wifi_ddlist_ssid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_wifi_ddlist_ssid, lv_color_hex(0xe1e6ee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_wifi_ddlist_ssid, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_wifi_ddlist_ssid, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_wifi_ddlist_ssid, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_wifi_ddlist_ssid, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_ddlist_ssid, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_wifi_ddlist_ssid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wifi_ddlist_ssid, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_wifi_ddlist_ssid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wifi_ddlist_ssid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for &style_screen_wifi_ddlist_ssid_extra_list_selected_checked
	static lv_style_t style_screen_wifi_ddlist_ssid_extra_list_selected_checked;
	ui_init_style(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked);
	
	lv_style_set_border_width(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, 1);
	lv_style_set_border_opa(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, 255);
	lv_style_set_border_color(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, 3);
	lv_style_set_bg_opa(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, 255);
	lv_style_set_bg_color(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, lv_color_hex(0x00a1b5));
	lv_style_set_bg_grad_dir(&style_screen_wifi_ddlist_ssid_extra_list_selected_checked, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_wifi_ddlist_ssid), &style_screen_wifi_ddlist_ssid_extra_list_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_wifi_ddlist_ssid_extra_list_main_default
	static lv_style_t style_screen_wifi_ddlist_ssid_extra_list_main_default;
	ui_init_style(&style_screen_wifi_ddlist_ssid_extra_list_main_default);
	
	lv_style_set_max_height(&style_screen_wifi_ddlist_ssid_extra_list_main_default, 90);
	lv_style_set_text_color(&style_screen_wifi_ddlist_ssid_extra_list_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_wifi_ddlist_ssid_extra_list_main_default, &lv_font_montserratMedium_12);
	lv_style_set_text_opa(&style_screen_wifi_ddlist_ssid_extra_list_main_default, 255);
	lv_style_set_border_width(&style_screen_wifi_ddlist_ssid_extra_list_main_default, 1);
	lv_style_set_border_opa(&style_screen_wifi_ddlist_ssid_extra_list_main_default, 255);
	lv_style_set_border_color(&style_screen_wifi_ddlist_ssid_extra_list_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_wifi_ddlist_ssid_extra_list_main_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_wifi_ddlist_ssid_extra_list_main_default, 3);
	lv_style_set_bg_opa(&style_screen_wifi_ddlist_ssid_extra_list_main_default, 255);
	lv_style_set_bg_color(&style_screen_wifi_ddlist_ssid_extra_list_main_default, lv_color_hex(0xffffff));
	lv_style_set_bg_grad_dir(&style_screen_wifi_ddlist_ssid_extra_list_main_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_wifi_ddlist_ssid), &style_screen_wifi_ddlist_ssid_extra_list_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default
	static lv_style_t style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default;
	ui_init_style(&style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default);
	
	lv_style_set_radius(&style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default, lv_color_hex(0x00ff00));
	lv_style_set_bg_grad_dir(&style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default, LV_GRAD_DIR_NONE);
	lv_obj_add_style(lv_dropdown_get_list(ui->screen_wifi_ddlist_ssid), &style_screen_wifi_ddlist_ssid_extra_list_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_wifi_btn_connect
	ui->screen_wifi_btn_connect = lv_btn_create(ui->screen_wifi);
	ui->screen_wifi_btn_connect_label = lv_label_create(ui->screen_wifi_btn_connect);
	lv_label_set_text(ui->screen_wifi_btn_connect_label, "连接");
	lv_label_set_long_mode(ui->screen_wifi_btn_connect_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_wifi_btn_connect_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_wifi_btn_connect, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_wifi_btn_connect_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_wifi_btn_connect, 32, 133);
	lv_obj_set_size(ui->screen_wifi_btn_connect, 256, 34);

	//Write style for screen_wifi_btn_connect, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wifi_btn_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wifi_btn_connect, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_wifi_btn_connect, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_wifi_btn_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_btn_connect, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wifi_btn_connect, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_wifi_btn_connect, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_wifi_btn_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_wifi_btn_connect, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_wifi_btn_connect, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_wifi_btn_connect, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wifi_btn_connect, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wifi_btn_connect, &lv_font_pingfang_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_wifi_btn_connect, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wifi_btn_connect, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_wifi_btn_rescan
	ui->screen_wifi_btn_rescan = lv_btn_create(ui->screen_wifi);
	ui->screen_wifi_btn_rescan_label = lv_label_create(ui->screen_wifi_btn_rescan);
	lv_label_set_text(ui->screen_wifi_btn_rescan_label, "刷新");
	lv_label_set_long_mode(ui->screen_wifi_btn_rescan_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_wifi_btn_rescan_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_wifi_btn_rescan, 0, LV_STATE_DEFAULT);
	lv_obj_set_width(ui->screen_wifi_btn_rescan_label, LV_PCT(100));
	lv_obj_set_pos(ui->screen_wifi_btn_rescan, 246, 37);
	lv_obj_set_size(ui->screen_wifi_btn_rescan, 64, 64);

	//Write style for screen_wifi_btn_rescan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_wifi_btn_rescan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_wifi_btn_rescan, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_wifi_btn_rescan, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_wifi_btn_rescan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_wifi_btn_rescan, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_wifi_btn_rescan, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_wifi_btn_rescan, lv_color_hex(0x0d4b3b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_wifi_btn_rescan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_wifi_btn_rescan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_wifi_btn_rescan, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_wifi_btn_rescan, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_wifi_btn_rescan, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_wifi_btn_rescan, &lv_font_pingfang_18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_wifi_btn_rescan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_wifi_btn_rescan, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of screen_wifi.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_wifi);

	//Init events for screen.
	events_init_screen_wifi(ui);
}
