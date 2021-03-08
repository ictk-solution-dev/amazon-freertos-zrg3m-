/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

 
#include "bt_hci.h"
#include "bt_gap_le.h"
#include "bt_debug.h"
#include "BLE_config.h"


/* ---------------------------------------------------------------------------- */

/* Create the log control block as user wishes. Here we use 'app' as module name.
 * User needs to define their own log control blocks as project needs.
 * Please refer to the log dev guide under /doc folder for more details.
 */
log_create_module(app, PRINT_LEVEL_INFO);

/* ---------------------------------------------------------------------------- */

#define APP_BLE_SMTCN_MAX_INTERVAL          0x00C0    /*The range is from 0x0020 to 0x4000.*/
#define APP_BLE_SMTCN_MIN_INTERVAL          0x00C0    /*The range is from 0x0020 to 0x4000.*/
#define APP_BLE_SMTCN_CHANNEL_NUM           7
#define APP_BLE_SMTCN_FILTER_POLICY         0
#define APP_BLE_SMTCN_AD_FLAG_LEN           2
#define APP_BLE_SMTCN_AD_UUID_LEN           3


static void app_start_advertising(void)
{
    // start advertising
    bt_hci_cmd_le_set_advertising_enable_t enable;
    bt_hci_cmd_le_set_advertising_parameters_t adv_param = {
            .advertising_interval_min = APP_BLE_SMTCN_MIN_INTERVAL,
            .advertising_interval_max = APP_BLE_SMTCN_MAX_INTERVAL,
            .advertising_type = BT_HCI_ADV_TYPE_CONNECTABLE_UNDIRECTED,
            .own_address_type = BT_ADDR_RANDOM,
            .advertising_channel_map = APP_BLE_SMTCN_CHANNEL_NUM,
            .advertising_filter_policy = APP_BLE_SMTCN_FILTER_POLICY
        };
    bt_hci_cmd_le_set_advertising_data_t adv_data;

    adv_data.advertising_data[0] = APP_BLE_SMTCN_AD_FLAG_LEN;   // 2
    adv_data.advertising_data[1] = BT_GAP_LE_AD_TYPE_FLAG;      // 0x01
    adv_data.advertising_data[2] = BT_GAP_LE_AD_FLAG_BR_EDR_NOT_SUPPORTED | BT_GAP_LE_AD_FLAG_GENERAL_DISCOVERABLE;

    adv_data.advertising_data[3] = APP_BLE_SMTCN_AD_UUID_LEN;
    adv_data.advertising_data[4] = BT_GAP_LE_AD_TYPE_16_BIT_UUID_COMPLETE;
    adv_data.advertising_data[5] = APP_BLE_SMTCN_SERVICE_UUID & 0x00FF;
    adv_data.advertising_data[6] = (APP_BLE_SMTCN_SERVICE_UUID & 0xFF00)>>8;

    adv_data.advertising_data[7] = 1+strlen(APP_BLE_SMTCN_DEVICE_NAME);
    adv_data.advertising_data[8] = BT_GAP_LE_AD_TYPE_NAME_COMPLETE;
    memcpy(adv_data.advertising_data+9, APP_BLE_SMTCN_DEVICE_NAME, strlen(APP_BLE_SMTCN_DEVICE_NAME));

    adv_data.advertising_data_length = 9 + strlen(APP_BLE_SMTCN_DEVICE_NAME);

    enable.advertising_enable = BT_HCI_ENABLE;
    bt_gap_le_set_advertising(&enable, &adv_param, &adv_data, NULL);
}

extern bt_bd_addr_t local_public_addr;

// called by bt_app_event_callback@bt_common.c
bt_status_t app_bt_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{
    LOG_I(app, "---> bt_event_callback(0x%08X,%d)", msg, status);

    switch(msg)
    {
    case BT_POWER_ON_CNF:
        LOG_I(app, "[BT_POWER_ON_CNF](%d)", status);

        // set random address before advertising
        LOG_I(app, "bt_gap_le_set_random_address()");    
        bt_gap_le_set_random_address((bt_bd_addr_ptr_t)local_public_addr);
        break;

    case BT_GAP_LE_SET_RANDOM_ADDRESS_CNF: 
        LOG_I(app, "[BT_GAP_LE_SET_RANDOM_ADDRESS_CNF](%d)", status);

        // start advertising
        app_start_advertising();
        break;

    case BT_GAP_LE_SET_ADVERTISING_CNF:
        LOG_I(app, "[BT_GAP_LE_SET_ADVERTISING_CNF](%d)", status);
        break;

    case BT_GAP_LE_DISCONNECT_IND:
        LOG_I(app, "[BT_GAP_LE_DISCONNECT_IND](%d)", status);

        // start advertising
        app_start_advertising();
        break;

    case BT_GAP_LE_CONNECT_IND:
        LOG_I(app, "[BT_GAP_LE_CONNECT_IND](%d)", status);

        bt_gap_le_connection_ind_t *connection_ind = (bt_gap_le_connection_ind_t *)buff;
        LOG_I(app, "-> connection handle = 0x%04x, role = %s", connection_ind->connection_handle, (connection_ind->role == BT_ROLE_MASTER)? "master" : "slave");

        LOG_I(app, "************************");
        LOG_I(app, "BLE connected!!");
        LOG_I(app, "************************");
        break;
    }

    LOG_I(app, "<--- bt_event_callback(0x%08X,%d)", msg, status);
    return BT_STATUS_SUCCESS;
}




static bt_gap_le_smp_pairing_config_t pairing_config = {//mitm, bond, oob
    .maximum_encryption_key_size = 16,
    .io_capability = BT_GAP_LE_SMP_NO_INPUT_NO_OUTPUT,
    .auth_req = BT_GAP_LE_SMP_AUTH_REQ_BONDING,
    .oob_data_flag = BT_GAP_LE_SMP_OOB_DATA_NOT_PRESENTED,
    .initiator_key_distribution = BT_GAP_LE_SMP_KEY_DISTRIBUTE_ENCKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_IDKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_SIGN,
    .responder_key_distribution = BT_GAP_LE_SMP_KEY_DISTRIBUTE_ENCKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_IDKEY | BT_GAP_LE_SMP_KEY_DISTRIBUTE_SIGN,
};

static bt_gap_le_local_key_t local_key = {
    .encryption_info.ltk = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc8, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf },
    .master_id.ediv = 0x1005,
    .master_id.rand = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7 },
    .identity_info.irk = { 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf },
    .signing_info.csrk = { 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf }
};

static bt_gap_le_bonding_info_t  bonding_info;
static bool sc_only = false;
static bt_gap_le_local_config_req_ind_t local_config;

//static uint16_t g_conn_interval;

extern bt_status_t app_bt_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff);

/**
 * @brief   This function is a static callback for the application to listen to the event. Provide a user-defined callback.
 * @param[in] msg     is the callback message type.
 * @param[in] status  is the status of the callback message.
 * @param[in] buf     is the payload of the callback message.
 * @return            The status of this operation returned from the callback.
 */

bt_status_t bt_app_event_callback(bt_msg_type_t msg, bt_status_t status, void *buff)
{
    // bypass to app_bt_event_callback@main.c
    return app_bt_event_callback(msg, status, buff);
}

/**
 * @brief     This API invoked by the SDK process should be implemented by the application. The application should return the Local Configuration field.
 * @return    The loacl configuration pointer, please set the local key and secure connection mode flag. The pointer should not be NULL and it must be a global variable.
 */
bt_gap_le_local_config_req_ind_t *bt_gap_le_get_local_config(void)
{
    local_config.local_key_req = &local_key;
    local_config.sc_only_mode_req = sc_only;
 
    return &local_config;
}

/**
 * @brief   This API invoked by the SDK process should be implemented by the application. The application should return the Bonding Information field.
 * @param[in] remote_addr The address of the remote device to be bonded.
 * @return                The Bonding Information pointer, please set a pointer to the connection bonding information. The pointer should not be NULL and it must be a global variable.
 */
bt_gap_le_bonding_info_t *bt_gap_le_get_bonding_info(const bt_addr_t remote_addr)
{
    return &bonding_info;
}

/**
 * @brief   This API invoked by the SDK process should be implemented by the application. The application should return the Pairing Configuration field.
 * @param[in] ind         Bonding start indication structure. Application should set the pairing_config_req variable to a global variable.
 * @return    #BT_STATUS_SUCCESS, the application set the pairing configuration successfully.
 *            #BT_STATUS_OUT_OF_MEMORY, out of memory.
 */
bt_status_t bt_gap_le_get_pairing_config(bt_gap_le_bonding_start_ind_t *ind)
{
    ind->pairing_config_req = pairing_config;

    return BT_STATUS_SUCCESS;
}


