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



void setup_scr_screen_main(lv_ui *ui)
{
	//Write codes screen_main
	ui->screen_main = lv_obj_create(NULL);
	ui->g_kb_screen_main = lv_keyboard_create(ui->screen_main);
	lv_obj_add_event_cb(ui->g_kb_screen_main, kb_event_cb, LV_EVENT_ALL, NULL);
	lv_obj_add_flag(ui->g_kb_screen_main, LV_OBJ_FLAG_HIDDEN);
	lv_obj_set_style_text_font(ui->g_kb_screen_main, &lv_font_SourceHanSerifSC_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_size(ui->screen_main, 320, 240);
	lv_obj_set_scrollbar_mode(ui->screen_main, LV_SCROLLBAR_MODE_AUTO);

	//Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_slider_1
	ui->screen_main_slider_1 = lv_slider_create(ui->screen_main);
	lv_slider_set_range(ui->screen_main_slider_1, 0, 100);
	lv_slider_set_mode(ui->screen_main_slider_1, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_main_slider_1, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_main_slider_1, 77, 221);
	lv_obj_set_size(ui->screen_main_slider_1, 213, 3);

	//Write style for screen_main_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_slider_1, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_slider_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_main_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_slider_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_main_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_slider_1, lv_color_hex(0x2195f6), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes screen_main_label_1
	ui->screen_main_label_1 = lv_label_create(ui->screen_main);
	lv_label_set_text(ui->screen_main_label_1, "Q:");
	lv_label_set_long_mode(ui->screen_main_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_1, 13, 27);
	lv_obj_set_size(ui->screen_main_label_1, 32, 17);

	//Write style for screen_main_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_main_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_2
	ui->screen_main_label_2 = lv_label_create(ui->screen_main);
	lv_label_set_text(ui->screen_main_label_2, "A:");
	lv_label_set_long_mode(ui->screen_main_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_2, 13, 64);
	lv_obj_set_size(ui->screen_main_label_2, 32, 17);

	//Write style for screen_main_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_main_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_3
	ui->screen_main_label_3 = lv_label_create(ui->screen_main);
	lv_label_set_text(ui->screen_main_label_3, "Volumn\n");
	lv_label_set_long_mode(ui->screen_main_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_3, -15, 214);
	lv_obj_set_size(ui->screen_main_label_3, 100, 32);

	//Write style for screen_main_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_3, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_main_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_ta_question
	ui->screen_main_ta_question = lv_textarea_create(ui->screen_main);
	lv_textarea_set_text(ui->screen_main_ta_question, "Hello World");
	lv_textarea_set_placeholder_text(ui->screen_main_ta_question, "");
	lv_textarea_set_password_bullet(ui->screen_main_ta_question, "*");
	lv_textarea_set_password_mode(ui->screen_main_ta_question, false);
	lv_textarea_set_one_line(ui->screen_main_ta_question, false);
	lv_textarea_set_accepted_chars(ui->screen_main_ta_question, "");
	lv_textarea_set_max_length(ui->screen_main_ta_question, 32);
	#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
		lv_obj_add_event_cb(ui->screen_main_ta_question, ta_event_cb, LV_EVENT_ALL, ui->g_kb_screen_main);
	#endif
	lv_obj_set_pos(ui->screen_main_ta_question, 63, 25);
	lv_obj_set_size(ui->screen_main_ta_question, 240, 26);

	//Write style for screen_main_ta_question, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_main_ta_question, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_ta_question, &lv_font_arial_8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_main_ta_question, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_ta_question, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_ta_question, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_ta_question, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_ta_question, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_ta_question, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_ta_question, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_ta_question, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_ta_question, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_ta_question, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_ta_question, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_ta_question, 6, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_ta_question, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_ta_question, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_ta_question, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_ta_question, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_ta_question, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write codes screen_main_ta_answer
	ui->screen_main_ta_answer = lv_textarea_create(ui->screen_main);
	lv_textarea_set_text(ui->screen_main_ta_answer, "Hello World");
	lv_textarea_set_placeholder_text(ui->screen_main_ta_answer, "");
	lv_textarea_set_password_bullet(ui->screen_main_ta_answer, "*");
	lv_textarea_set_password_mode(ui->screen_main_ta_answer, false);
	lv_textarea_set_one_line(ui->screen_main_ta_answer, false);
	lv_textarea_set_accepted_chars(ui->screen_main_ta_answer, "");
	lv_textarea_set_max_length(ui->screen_main_ta_answer, 100);
	#if LV_USE_KEYBOARD != 0 || LV_USE_ZH_KEYBOARD != 0
		lv_obj_add_event_cb(ui->screen_main_ta_answer, ta_event_cb, LV_EVENT_ALL, ui->g_kb_screen_main);
	#endif
	lv_obj_set_pos(ui->screen_main_ta_answer, 63, 62);
	lv_obj_set_size(ui->screen_main_ta_answer, 240, 137);

	//Write style for screen_main_ta_answer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_main_ta_answer, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_ta_answer, &lv_font_arial_8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_main_ta_answer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_ta_answer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_ta_answer, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_ta_answer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_ta_answer, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_ta_answer, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_ta_answer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_ta_answer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_ta_answer, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_ta_answer, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_ta_answer, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_ta_answer, 6, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_ta_answer, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_ta_answer, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_ta_answer, lv_color_hex(0x2195f6), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_ta_answer, LV_GRAD_DIR_NONE, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_ta_answer, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//The custom code of screen_main.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_main);

}
