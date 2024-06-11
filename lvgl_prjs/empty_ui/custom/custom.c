/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#include "events_init.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
extern lv_ui guider_ui;
/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

void gui_wifi_screen_clear_ssid()
{
    lv_dropdown_clear_options(guider_ui.screen_wifi_ddlist_ssid);
}

void gui_wifi_screen_add_ssid(char *ssid)
{
    lv_dropdown_set_selected(guider_ui.screen_wifi_ddlist_ssid, LV_DROPDOWN_POS_LAST);
    lv_dropdown_add_option(guider_ui.screen_wifi_ddlist_ssid, ssid, LV_DROPDOWN_POS_LAST);
}
