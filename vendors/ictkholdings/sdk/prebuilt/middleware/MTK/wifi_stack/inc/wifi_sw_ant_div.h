/* Copyright Statement:
 *
 * (C) 2018  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

/* This file add for SW antenna diversity feature */

#ifndef WIFI_SW_ANT_DIV_H__
#define WIFI_SW_ANT_DIV_H__



#include "hal_gpio_internal.h"
#include "hal_gpio.h"
#include "wifi_os_api.h"

typedef struct __antenna_param
{
    uint8_t ant_diversity_on;
    uint8_t timer_period;
    uint8_t rssi_threshold;
    uint8_t ant_numer;
    uint8_t short_period;
    uint8_t beacon_n;
    uint8_t beacon_t;
    uint8_t idle_flag;
    uint8_t max_idle_time;
    uint8_t ant1;
    uint8_t ant2;
    int32_t rssi;
    uint32_t last_tx_tick;
    int32_t collect_beacon_count;
    os_tmr_t short_period_timer;
    os_tmr_t normal_period_timer;
    os_semaphore_t get_rssi_semphr;
}antenna_param_t;

int32_t wifi_select_ant_1(void);

int32_t wifi_select_ant_2(void);

int32_t wifi_close_ant1_ant2(void);

int8_t wifi_is_ant_diversity_on(void);

int8_t wifi_is_upper_idle(void);

int8_t wifi_get_ant_timer_period(void);

int8_t wifi_get_ant_rssi_threshold(void);

int8_t wifi_get_ant_short_period(void);

int8_t wifi_get_ant_beacon_n_num(void);

int8_t wifi_get_ant_beacon_t_num(void);

uint8_t wifi_get_ant_default_num(void);

int32_t wifi_start_ant_diversity_normal_timer(uint8_t is_first);

void wifi_ant_calc_average_rssi(int32_t       snr);
antenna_param_t* wifi_get_ant_param(void);
//int32_t get_antenna_diversity_flag(void);
int32_t wifi_get_collect_beacon_count(void);
void wifi_set_ant_last_tx_tick(uint32_t value);
int32_t wifi_delete_ant_timer(void);
int32_t wifi_ant_div_init(void);
void wifi_ant_diversity_on_off(uint8_t onoff);


#endif
