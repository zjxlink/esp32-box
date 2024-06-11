/*
 * @Author: ZhouJie
 * @version: 1.0
 * @Date: 2024-05-31 19:11:30
 * @LastEditors: ZhouJie
 * @LastEditTime: 2024-05-31 21:56:51
 * @Descripttion: 
 */
/*
 * SPDX-FileCopyrightText: 2015-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char* req_asr(uint8_t *audio_buffer, size_t audio_buffer_len);

#ifdef __cplusplus
}
#endif
