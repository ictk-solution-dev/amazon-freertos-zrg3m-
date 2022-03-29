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

/**
 * @file wifi_default_config.h
 *
 * Wi-Fi  configuration / settings for the use, include default value, avaiable value, and internel use.
 *
 */

/**@addtogroup WIFI_CONFIG
* @{
* This section introduces the Wi-Fi driver configuration / settings allowed.
* We suggest use our default parameters. If you want to modify the default value, you can depend on the usage level
* to change feasible value.
* There are three level for every item
* Value                         |Definition                                                              |
* ------------------------------|-----------------------------------|
* \b User_can_modify                        | User can modify depend on user requirements |
* \b Confirm_with_Airoha                   | User cannot modify without confirm with Airoha |
* \b Internel_use                              | User cannot modify, only internal use |
* \b Not_supported                           | Not supported |
*
*
*/


#ifndef __WIFI_DEFAULT_CONFIG_H__
#define __WIFI_DEFAULT_CONFIG_H__


#include "connsys_profile.h"
#include "wifi_init.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@defgroup WIFI_CONFIGURATION Configuration
* @{
*/

/**@brief OpMode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: OpMode \n
*     1.Default: 1, #WIFI_MODE_STA_ONLY, means station mode. \n
*     2.Optional: 1-4. Please refer #wifi_config_set_opmode() for detail. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_OPMODE                 ("1")

/**@brief CountryCode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: CountryCode \n
*     1.Default: TW, means TaiWan. \n
*     2.Optional: by user requirement. Please refer #wifi_config_set_country_code() for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697. 
* @note 2.Set country code will not auto set channel list, you should set channel list refer 
*  user guide or your requirement. It just used to set the country string in contry IE, not set channel setting.
*
*/
#define WIFI_DEFAULT_COUNTRY_CODE           ("TW")

/**@brief CountryRegion, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: CountryRegion \n
*     1.Default: 5, means channel1-14. \n
*     2.Optional: by user requirement. Please refer #wifi_config_set_country_region() for detail. \n
*
* @note Not Supported.
*/
#define WIFI_DEFAULT_COUNTRY_REGION         ("5")

/**@brief CountryRegionABand, the device used at startup.
*
*  Usage: #Not_supported.  \n
*  Dependence: No. \n 
*
* @param[in] String: CountryRegionABand \n
*     1.Default: 3, means CH52, 56, 60, 64, 149, 153, 157, 161. \n
*     2.Optional: by user requirement. Please refer #wifi_config_set_country_region() for detail. \n
*
* @note Not Supported.
*/
#define WIFI_DEFAULT_COUNTRY_REGION_A_BAND  ("3")

/**@brief RadioOff, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: RadioOff \n
*     1.Default: 0, WiFi radio is not off at start(default is on). \n
*     2.Optional: 1. WiFi radio is off at start. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_RADIO_ONOFF            ("0")

/**@brief DbgLevel, the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: DbgLevel \n
*     1.Default: 3, error level. \n
*     2.Optional: ?. \n
*
* @note Support MT7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_N9_DEBUG_LEVEL         ("3")

/**@brief RTSThreshold, when packet length is longer than this threshold, it will trigger RTS flow. the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: RTSThreshold \n
*     1.Default: 2347, packet length. \n
*     2.Optional: ?. \n
*
* @note Support 7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_RTS_THRESHOLD          ("2347")

/**@brief FragThreshold, when packet length is longer than this threshold, it will trigger fragmentation. the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: FragThreshold \n
*     1.Default: 2346, packet length. \n
*     2.Optional: ?. \n
*
* @note Support 7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_FRAGMENT_THRESHOLD     ("2346")

/**@brief BGChannelTable, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: BGChannelTable, format is "start_channel,number of channel,active scan/passive scan|". \n
*     1.Default: "1,14,0", means first_channel=1, num_of_ch=14,channel_prop=0(active). \n
*     2.Optional: by user requirement. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The limited group number is 10.
*/
#define WIFI_DEFAULT_BG_CHANNEL_TABLE       ("1,14,0|")    //first_channel=1, num_of_ch=14,channel_prop=0(active)

/**@brief AChannelTable, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: AChannelTable, format is "start_channel,number of channel,active scan/passive scan|". \n
*     1.Default: "36,8,0|100,11,0|149,4,0|", there are 3 group channel list. Group1 start at channel 36, number of channel is 8, 0 means active scan.
*     Group2 start at channel 100, number of channel is 1, 0 means active scan. Group3 start at channel 149, number of channel is 4, 0 means active scan. \n
*     2.Optional: by user requirement. \n
*
* @note 1. Support MT7687/7697.
* @note 2. The limited group number is 10.
*/
#define WIFI_DEFAULT_A_CHANNEL_TABLE        ("36,8,0|100,11,0|149,4,0|")

/**@brief syslog_filters, the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: syslog_filters \n
*     1.Default: "", default is NULL. \n
*     2.Optional: NULL. \n
*
* @note Support MT7687/7697.
*/
#define WIFI_DEFAULT_SYSLOG_FILTERS         ("")

/**@brief WiFiPrivilegeEnable, the device used at startup.For checking if BLE ON OFF based on project (set depending on project).
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: WiFiPrivilegeEnable \n
*     1.Default: 1,enable. \n
*     2.Optional: 0, diasble. \n
*
* @note Support c4sp MT7697, if #MTK_WIFI_PRIVILEGE_ENABLE the default is 1, else is 0.
*/
#ifdef MTK_WIFI_PRIVILEGE_ENABLE
#define WIFI_DEFAULT_WIFI_PRIVILEGE_ENABLE  ("1")
#else
#define WIFI_DEFAULT_WIFI_PRIVILEGE_ENABLE  ("0")
#endif


/**@brief StaFastLink, the value at station mode, the device used at startup.Bootup-time optimization for c4sp (set only for c4sp)
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: StaFastLink \n
*     1.Default: 0 enable the fast_link feature. \n
*     2.Optional: 1 disable the fast_lin feature. \n
*
* @note Support c4sp MT7697.
*/
#define WIFI_DEFAULT_STA_FAST_LINK          ("0")

/**@brief LocalAdminMAC, the value at station mode, the device used at startup. Set to use the EEPROM defined MAC address, instead of hardcoded MAC address in FW(hardly used).
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: LocalAdminMAC \n
*     1.Default: 1, enable local admin mac address. \n
*     2.Optional: 0, disable local admin mac address. \n
*
* @note Support MT7697.
*/
#define WIFI_DEFAULT_STA_LOCAL_ADMIN_MAC    ("1")

/**@brief MacAddr, mac address at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: MacAddr \n
*     1.Default: "00:0c:43:76:87:22". \n
*     2.Optional: by user requirement. \n
*
* @note 1. Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2. If efuse is avaiable, first use efuse mac address, else use defalut mac address..
*/
#define WIFI_DEFAULT_STA_MAC_ADDR           ("00:0c:43:76:87:22")

/**@brief Ssid, the target AP ssid at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: Ssid \n
*     1.Default: "MTK_SOFT_AP". \n
*     2.Optional: by user requirement. The maximum length is #WIFI_MAX_LENGTH_OF_SSID in bytes. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_STA_SSID length is change, the WIFI_DEFAULT_STA_SSID_LEN should be change at the same time. 
*/
#define WIFI_DEFAULT_STA_SSID               ("MTK_SOFT_AP")

/**@brief SsidLen, the target AP ssid length at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: SsidLen \n
*     1.Default: 11. \n
*     2.Optional: depend on WIFI_DEFAULT_STA_SSID. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_STA_SSID is change, the WIFI_DEFAULT_STA_SSID_LEN should be change at the same time.
*/
#define WIFI_DEFAULT_STA_SSID_LEN           ("11")

/**@brief BssType, the channel at station mode, the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: No. \n 
*
* @param[in] String: BssType \n
*     1.Default: 1. \n
*     2.Optional: No. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697
*/
#define WIFI_DEFAULT_STA_BSS_TYPE           ("1")

/**@brief Channel, the channel at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: Channel \n
*     1.Default: 1. \n
*     2.Optional: by user requirement. Supported 2.4G/5G avaiable channel. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_CHANNEL            ("1")

/**@brief BW, the bandwidth at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: BW \n
*     1.Default: 0, #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ. \n
*     2.Optional: 1. Please refer #wifi_config_set_bandwidth() for detail. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_BANDWIDTH          ("0")

/**@brief WirelessMode, the wireless mode at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WirelessMode \n
*     1.Default: 9,WIFI_PHY_11BGN_MIXED. \n
*     2.Optional: please refer #wifi_phy_mode_t for detail.\n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_WIRELESS_MODE      ("9")

/**@brief BADecline, device decide allow/reject ADDBA request from originator.
*
*  Usage: #User_can_modify.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: BADecline \n
*     1.Default: 1, reject ADDBA request from originator. \n
*     2.0, allow ADDBA request from originator. \n
*
* @note Support 7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_BA_DECLINE         ("1") // Disable 11e BA, reject ADDBA request from peer

/**@brief AutoBA, the send ADDBA request at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: 802.11n is enable. Feature MTK_WIFI_TGN_VERIFY_ENABLE. \n 
*
* @param[in] String: AutoBA \n
*     1.Default: 0, disable AutoBA. Do not send ADDBA request to peer to set up a BA session. \n
*     2.Optional: 1, enable AutoBA. Do send ADDBA request to peer to set up a BA session. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.If do TGn test, the autoBA should be 0.
*/
#if defined(MTK_WIFI_TGN_VERIFY_ENABLE)
#define WIFI_DEFAULT_STA_AUTO_BA            ("0")  /*If do TGn test, the autoBA should be 0*/
#else
#define WIFI_DEFAULT_STA_AUTO_BA            ("0") // Disable 11e BA, Do not send ADDBA request to peer to set up a BA session
#endif

/**@brief HT_MCS, the HT MCS(Modulation and Coding Scheme) value at station mode, the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_MCS \n
*     1.Default: 33. \n
*     2.Optional: ? . \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_HT_MCS             ("33")

/**@brief HT_BAWinSize, the HT ADDBA window size for station mode, respone to originator, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_BAWinSize \n
*     1.Default: 64, the initialy BlockACK window size, and the really used BlockACK window size maybe depend on negotiation.  \n
*     2.Optional: 1~maximum_ba_size, the initialy BlockACK window size. \n
*
* @note 1.Support MT7687/7697, the default is 64, the maximum_ba_size is 64.
* @note 2.Support MT5932/7682/7686/7698, the default is 4, the maximum_ba_size is 4.
*/
#if (PRODUCT_VERSION == 7687 || PRODUCT_VERSION == 7697)
#define WIFI_DEFAULT_STA_HT_BA_WINDOW_SIZE  ("64")
#elif (PRODUCT_VERSION == 7698 || PRODUCT_VERSION == 7686 || PRODUCT_VERSION == 7682 || PRODUCT_VERSION == 5932)
#define WIFI_DEFAULT_STA_HT_BA_WINDOW_SIZE  ("4")
#endif

/**@brief HT_GI, the HT_GI value at station mode, the device used at startup. To set the ht phy mode setting as "Short Guard Interval" in sta mode.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_GI \n
*     1.Default: 1, enable. \n
*     2.Optional: 0, diaable . \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_HT_GI              ("1")

/**@brief HT_PROTECT, the HT_PROTECT value at station mode, the device used at startup. Station follows the protection mode settings \n
* as per the AP's IE (Additional HT information Element Operation Mode).
*
*  Usage: #Not_Supported.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_PROTECT \n
*     1.Default: 1. enable HT_PROTECT feature\n
*     2.Optional: NULL. \n
*
* @note Not Supported.
*/
#define WIFI_DEFAULT_STA_HT_PROTECT         ("1")

/**@brief HT_EXTCHA, the value at station mode, the device used at startup. For 40 MHz case it helps to decide the center channel ,\n
* Secondary channel is above or below.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_EXTCHA \n
*     1.Default: 1. enable HT_EXTCHA feature\n
*     2.Optional: 0, disbale. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_HT_EXT_CHANNEL     ("1")

/**@brief WmmCapable, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WmmCapable \n
*     1.Default: 0, disable 802.11e WMM based on EDCA. \n
*     2.Optional: 1, enable 802.11e WMM based on EDCA. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_WMM_CAPABLE        ("0") // Disable 11e WMM based on EDCA

/**@brief ListenInterval, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: ListenInterval \n
*     1.Default: 1, every listen interval to listen beacon from AP. \n
*     2.Optional: Please refer #wifi_config_set_listen_interval() for detail. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_LISTEN_INTERVAL    ("1")

/**@brief AuthMode, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: AuthMode \n
*     1.Default: 0, WIFI_AUTH_MODE_OPEN. \n
*     2.Optional: Please refer #wifi_auth_mode_t get for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The WIFI_DEFAULT_STA_AUTH_MODE/WIFI_DEFAULT_STA_ENCRYPT_TYPE value 0/1 means station auto mapping the SoftAP security mode.
*/
#define WIFI_DEFAULT_STA_AUTH_MODE          ("0")

/**@brief EncrypType, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: EncrypType \n
*     1.Default: 0, WIFI_ENCRYPT_TYPE_WEP_DISABLED. \n
*     2.Optional: Please refer #wifi_encrypt_type_t for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The WIFI_DEFAULT_STA_AUTH_MODE/WIFI_DEFAULT_STA_ENCRYPT_TYPE value 0/1 means station auto mapping the SoftAP security mode.
*/
#define WIFI_DEFAULT_STA_ENCRYPT_TYPE       ("1")

/**@brief WpaPsk, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WpaPsk \n
*     1.Default: 12345678. \n
*     2.Optional: User can modify by requirement. passphrase is 8 to 63 bytes ASCII. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_STA_WPA_PSK length is change, the WIFI_DEFAULT_STA_WPA_PSK_LEN should be change at same time. 
*/
#define WIFI_DEFAULT_STA_WPA_PSK            ("12345678")

/**@brief WpaPskLen, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WpaPskLen \n
*     1.Default: 8. \n
*     2.Optional: depend on WIFI_DEFAULT_STA_WPA_PSK. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_STA_WPA_PSK length is change, the WIFI_DEFAULT_STA_WPA_PSK_LEN should be change at same time. 
*/
#define WIFI_DEFAULT_STA_WPA_PSK_LEN        ("8")

/**@brief PairCipher, the value at station mode, the device used at startup. Just holds the value of encryptype in Ext command 0x03.
*
*  Usage: #Not_Supported.  \n
*  Dependence: No. \n 
*
* @param[in] String: PairCipher \n
*     1.Default: 0, disable PairCipher feature\n
*     2.Optional: NULL. \n
*
* @note Not Support.
*/
#define WIFI_DEFAULT_STA_PAIR_CIPHER        ("0")

/**@brief GroupCipher, the value at station mode, the device used at startup. 
*
*  Usage: #Not_Supported.  \n
*  Dependence: No. \n 
*
* @param[in] String: GroupCipher \n
*     1.Default: 0, disable GroupCipher feature\n
*     2.Optional: NULL. \n
*
* @note Not Support.
*/
#define WIFI_DEFAULT_STA_GROUP_CIPHER       ("0")

/**@brief DefaultKeyId, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: DefaultKeyId \n
*     1.Default: 0, the first share key to use. \n
*     2.Optional: 0~3, which group of share key to use. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_DEFAULT_KEY_ID     ("0")

/**@brief SharedKey, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify. \n
*  Dependence: No. \n 
*
* @param[in] String: SharedKey \n
*     1.Default: "11111,22222,33333,44444", the first group share key is 11111, the 2th group share key is 22222, the 3th group share key is 33333, the 4th group share key is 44444. \n
*     2.Optional: Please refer #wifi_config_set_wep_key() for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The 4 group share key WIFI_DEFAULT_STA_SHARE_KEY length should be right matched with WIFI_DEFAULT_STA_SHARE_KEY_LEN.
*/
#define WIFI_DEFAULT_STA_SHARE_KEY          ("12345,12345,12345,12345")

/**@brief SharedKeyLen, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify. \n
*  Dependence: No. \n 
*
* @param[in] String: SharedKeyLen \n
*     1.Default: "5,5,5,5", the first group share key length is 5,, the 2th group share key length is 5, the 3th group share key length is 5, the 4th group share key length is 5. \n
*     2.Optional: depend on WIFI_DEFAULT_STA_SHARE_KEY. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The 4 group share key WIFI_DEFAULT_STA_SHARE_KEY length should be right matched with WIFI_DEFAULT_STA_SHARE_KEY_LEN.
*/
#define WIFI_DEFAULT_STA_SHARE_KEY_LEN      ("5,5,5,5")

/**@brief PSMode, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: PSMode \n
*     1.Default: 0, #WIFI_POWER_SAVING_MODE_OFF. \n
*     2.Optional: 0-2, Please refer #wifi_power_saving_mode_t for detail.  \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_STA_POWER_SAVE_MODE    ("0")

/**@brief KeepAlivePeriod, the value at station mode, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: KeepAlivePeriod \n
*     1.Default: 10, station keep alive period is 10. \n
*     2.Optional: ? .  \n
*
* @note 1.Support MT7687/7697, the default is 10.
* @note 2.Support MT5932/7682/7686/7698, the default is 55.
*/
#if (PRODUCT_VERSION == 7687 || PRODUCT_VERSION == 7697)
#define WIFI_DEFAULT_STA_KEEP_ALIVE_PERIOD  ("10")
#elif (PRODUCT_VERSION == 7698 || PRODUCT_VERSION == 7686 || PRODUCT_VERSION == 7682 || PRODUCT_VERSION == 5932)
#define WIFI_DEFAULT_STA_KEEP_ALIVE_PERIOD  ("55")
#endif

/**@brief BeaconLostTime, if station failed to receive beacon from connected AP for the duration of BeaconLostTime, 
*  station will disconnect AP, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: Product Version. \n 
*
* @param[in] String: BeaconLostTime \n
*     1.Default: 30, station beacon lost time is 30 seconds. \n
*     2.Optional: 1-100 seconds.  \n
*
* @note 1.Support MT7698, the default is 30.
* @note 2.MT5932/7682/7686, MT7687/7697, the default is 5.
*/
#if (PRODUCT_VERSION == 7698)
#define WIFI_DEFAULT_STA_BEACON_LOST_TIME   ("30")
#else
#define WIFI_DEFAULT_STA_BEACON_LOST_TIME   ("5")
#endif

/**@brief ApcliBWAutoUpBelow, the value at station mode, the device used at startup. In 40 Hz BW for APCLI opmode , adapt to root AP's \n
* Extension Channel offset setting ,so the DUT's AP interface will also follow the root AP's setting ( to whom the APCLI is connected).
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: ApcliBWAutoUpBelow \n
*     1.Default: 1, enable the APCli bandwidth auto up and bellow. \n
*     2.Optional: 0, disable.  \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_APCLI_BW_AUTO_UP_BELOW ("1")

/**@brief StaKeepAlivePacket, the value at station mode, the device used at startup.
*
*  Usage: #Confirm with Airoha.
*  Dependence: No. \n 
*
* @param[in] String: StaKeepAlivePacket \n
*     1.Default: 1, the number of station keep alive packet is 1. \n
*     2.Optional: NULL.  \n
*
* @note Support MT7682/7686/7698.
*/
#define WIFI_DEFAULT_STA_KEEP_ALIVE_PACKET  ("1")

/**@brief ScanRound, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: ScanRound \n
*     1.Default: 30, the number of station scan round times to report target AP not find. \n
*     2.Optional: ?.  \n
*
* @note 1.Support MT7687/7697.
* @note 2.Host side use.
*/
#define WIFI_DEFAULT_STA_SCAN_ROUND         ("30")

/**@brief PMFCapability, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: fearure MTK_WIFI_PMF_ENABLE . \n 
*
* @param[in] String: PMFCapability \n
*     1.Default: 0, disable station mode PMF capability. \n
*     2.Optional: 1, enable station mode PMF capability.  \n
*     3.Optional: 2, require station mode PMF capability. \n
*
* @note Support MT7687/7697.
*/
#define WIFI_DEFAULT_STA_PMF_CAPABILITY     ("0")


/**@brief LocalAdminMAC, the value at SoftAP mode, the device used at startup. Set to use the EEPROM defined MAC address, instead of hardcoded MAC address in FW(hardly used).
*
*  Usage: #Not_Supported.
*  Dependence: No. \n 
*
* @param[in] String: LocalAdminMAC \n
*     1.Default: 1, enable local admin mac address. \n
*     2.Optional: 0, disable local admin mac address. \n
*
* @note Not supported.
*/
#define WIFI_DEFAULT_AP_LOCAL_ADMIN_MAC     ("1")

/**@brief MacAddr, mac address at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: MacAddr \n
*     1.Default: "00:0c:43:76:62:12". \n
*     2.Optional: by user requirement. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_MAC_ADDR            ("00:0c:43:76:62:12")

/**@brief Ssid, the ssid at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: Ssid \n
*     1.Default: "MTK_SOFT_AP". \n
*     2.Optional: by user requirement. The maximum length is #WIFI_MAX_LENGTH_OF_SSID in bytes. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_AP_SSID length is change, the WIFI_DEFAULT_AP_SSID_LEN should be change at same time. 
*/
#define WIFI_DEFAULT_AP_SSID                ("MTK_SOFT_AP")

/**@brief SsidLen, the ssid length at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: SsidLen \n
*     1.Default: 11. \n
*     2.Optional: depend on WIFI_DEFAULT_AP_SSID. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_AP_SSID length is change, the WIFI_DEFAULT_AP_SSID_LEN should be change at same time.
*/
#define WIFI_DEFAULT_AP_SSID_LEN            ("11")

/**@brief Channel, the channel for SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: Channel \n
*     1.Default: 1. \n
*     2.Optional: by user requirement. Supported 2.4G/5G avaiable channel. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_CHANNEL             ("1")

/**@brief BW, the bandwidth for SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: BW \n
*     1.Default: 0, #WIFI_IOT_COMMAND_CONFIG_BANDWIDTH_20MHZ. \n
*     2.Optional: 1. Please refer #wifi_config_set_bandwidth() for detail. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_BANDWIDTH           ("0")

/**@brief WirelessMode, the wireless mode for SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WirelessMode \n
*     1.Default: 9, WIFI_PHY_11BGN_MIXED. \n
*     2.Optional: Please refer #wifi_phy_mode_t for detail.\n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_WIRELESS_MODE       ("9")

/**@brief AutoBA, the Auto send ADDBA for SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: AutoBA \n
*     1.Default: 0, disable AutoBA. Do not send ADDBA request to peer to set up a BA session. \n
*     2.Optional: 1, enable AutoBA. Do send ADDBA request to peer to set up a BA session. \n
*
* @note Support 7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_AUTO_BA             ("0") // Disable 11e BA, Do not send ADDBA request to peer to set up a BA session

/**@brief HT_MCS, the HT MCS(Modulation and Coding Scheme) value at SoftAP mode, the device used at startup.
*
*  Usage: #Internel_use.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_MCS \n
*     1.Default: 33. \n
*     2.Optional: ?. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_HT_MCS              ("33")

/**@brief HT_BAWinSize, the HT BlockACK window size for softAP mode, respone to originator, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: Product Version. \n 
*
* @param[in] String: HT_BAWinSize \n
*     1.Default: 64, the initialy BlockACK window size, and the really used BlockACK window size maybe depend on negotiation.  \n
*     2.Optional: 1~maximum_ba_size, the initialy BlockACK window size.\n
*
* @note 1.Support MT7687/7697, the default is 64, the maximum_ba_size is 64. The suggest is 4 because of memory limited.
* @note 2.Support MT5932/7682/7686/7698, the default is 4, the maximum_ba_size is 4.
*/
#if (PRODUCT_VERSION == 7687 || PRODUCT_VERSION == 7697)
#define WIFI_DEFAULT_AP_HT_BA_WINDOW_SIZE   ("64")
#elif (PRODUCT_VERSION == 7698 || PRODUCT_VERSION == 7686 || PRODUCT_VERSION == 7682 || PRODUCT_VERSION == 5932)
#define WIFI_DEFAULT_AP_HT_BA_WINDOW_SIZE   ("4")
#endif

/**@brief HT_GI, the HT_GI(Guard Interval) value at SoftAP mode, the device used at startup.To set the ht phy mode setting as "Short Guard Interval" in ap mode.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_GI \n
*     1.Default: 1. enable HT GI feature. \n
*     2.Optional: 0, disable HT GI feature. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_HT_GI               ("1")

/**@brief HT_PROTECT, the HT_PROTECT value at SoftAP mode, the device used at startup. Update the protection mode setting for an Ap's BSS.
*
*  Usage: #Internel_use.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_PROTECT \n
*     1.Default: 1, enable HT_PROTECT feature. \n
*     2.Optional: 0, disable HT_PROTECT feature. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_HT_PROTECT          ("1")

/**@brief HT_EXTCHA, the HT_EXTCHA value at SoftAP mode, the device used at startup. For 40 MHz case , it gives the information about Extension channel offset \n
* ( if extension channel is above value is 1 , if it is below value is 3 and if it is 20 MHz case then value is 0 ). When set then it will lead to the AP interface disconnect with \n 
* all STAs and after adapting to root AP it will start beaconing again based on new setting.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: 802.11n is enable. \n 
*
* @param[in] String: HT_EXTCHA \n
*     1.Default: 1, enable HT_EXTCHA feature. \n
*     2.Optional: ?. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_HT_EXT_CHANNEL      ("1")

/**@brief WmmCapable. the WmmCapable value at SoftAP mode, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: WmmCapable \n
*     1.Default: 0, disable WmmCapable feature. \n
*     2.Optional: 1, enable WmmCapble feature. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_WMM_CAPABLE         ("0") // Disable 11e WMM based on EDCA

/**@brief DtimPeriod, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: DtimPeriod \n
*     1.Default: 1, broadcast and multicast data and let clients know when to wake up to receive those data. \n
*     2.Optional: Please refer #wifi_config_set_dtim_interval() for detail. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_DTIM_PERIOD         ("1")

/**@brief AuthMode, the value at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: AuthMode \n
*     1.Default: 0, WIFI_AUTH_MODE_OPEN. \n
*     2.Optional: Please refer #wifi_auth_mode_t for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The WIFI_DEFAULT_AP_AUTH_MODE/WIFI_DEFAULT_AP_WPA_PSK value 0/1 means the SoftAP security mode is open.
*/
#define WIFI_DEFAULT_AP_AUTH_MODE           ("0")

/**@brief EncrypType, the value at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: EncrypType \n
*     1.Default: 0, WIFI_ENCRYPT_TYPE_WEP_DISABLED. \n
*     2.Optional: Please refer #wifi_encrypt_type_t for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The WIFI_DEFAULT_AP_AUTH_MODE/WIFI_DEFAULT_AP_WPA_PSK value 0/1 means the SoftAP security mode is open.
*/
#define WIFI_DEFAULT_AP_ENCRYPT_TYPE        ("1")

/**@brief WpaPsk, the value at softap mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WpaPsk \n
*     1.Default: 12345678. \n
*     2.Optional: by user requirement. passphrase is 8 to 63 bytes ASCII. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_AP_WPA_PSK length is change, the WIFI_DEFAULT_AP_WPA_PSK_LEN should be change at same time. 
*/
#define WIFI_DEFAULT_AP_WPA_PSK             ("12345678")

/**@brief WpaPskLen, The value at softap mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: WpaPskLen \n
*     1.Default: 8. \n
*     2.Optional: depend on WIFI_DEFAULT_AP_WPA_PSK length. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.When WIFI_DEFAULT_AP_WPA_PSK length is change, the WIFI_DEFAULT_AP_WPA_PSK_LEN should be change at same time. 
*/
#define WIFI_DEFAULT_AP_WPA_PSK_LEN         ("8")

/**@brief PairCipher, The value at SoftAP mode, the device used at startup.
*
*  Usage: #Not_Supported.  \n
*  Dependence: No. \n 
*
* @param[in] String: PairCipher \n
*     1.Default: 0, disable PairCipher feature. \n
*     2.Optional: No. \n
*
* @note Not Supported.
*/
#define WIFI_DEFAULT_AP_PAIR_CIPHER         ("0")

/**@brief GroupCipher, the value at SoftAP mode, the device used at startup.
*
*  Usage: #Not_Supported.  \n
*  Dependence: No. \n 
*
* @param[in] String: GroupCipher \n
*     1.Default: 0, disable GroupCipher feature. \n
*     2.Optional: No. \n
*
* @note Not Supported.
*/
#define WIFI_DEFAULT_AP_GROUP_CIPHER        ("0")

/**@brief DefaultKeyId, the value at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: DefaultKeyId \n
*     1.Default: 0, the first share key to use. \n
*     2.Optional: 0~3. which group of share key to use. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_DEFAULT_KEY_ID      ("0")

/**@brief SharedKey, the value at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: SharedKey \n
*     1.Default: "11111,22222,33333,44444", the first group share key is 11111, the 2th group share key is 22222, the 3th group share key is 33333, the 4th group share key is 44444. \n
*     2.Optional: Please refer #wifi_config_set_wep_key() for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The 4 group share key WIFI_DEFAULT_AP_SHARE_KEY length should be right matched with WIFI_DEFAULT_AP_SHARE_KEY_LEN.
*/
#define WIFI_DEFAULT_AP_SHARE_KEY           ("11111,22222,33333,44444")

/**@brief SharedKeyLen, the value at SoftAP mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: No. \n 
*
* @param[in] String: SharedKeyLen \n
*     1.Default: "5,5,5,5", the first group share key length is 5,, the 2th group share key length is 5, the 3th group share key length is 5, the 4th group share key length is 5. \n
*     2.Optional: Please refer  #wifi_config_set_wep_key() for detail. \n
*
* @note 1.Support MT5932/7682/7686/7698, MT7687/7697.
* @note 2.The 4 group share key WIFI_DEFAULT_AP_SHARE_KEY length should be right matched with WIFI_DEFAULT_AP_SHARE_KEY_LEN.
*/
#define WIFI_DEFAULT_AP_SHARE_KEY_LEN       ("5,5,5,5")

/**@brief HideSSID, the value at SoftAP mode, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: HideSSID \n
*     1.Default: 0, disable SoftAP hidden ssid feature. \n
*     2.Optional: 1, enable SoftAP hidden ssid feature. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_HIDDEN_SSID         ("0")

/**@brief RekeyInterval, the value at SoftAP mode, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: RekeyInterval \n
*     1.Default: 3600, SoftAP rekey interval value. \n
*     2.Optional: ? . \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_REKEY_INTERVAL      ("3600")

/**@brief AutoChannelSelect, the value at SoftAP mode, the device used at startup.
*
*  Usage: #Confirm with Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: AutoChannelSelect \n
*     1.Default: 0, disable SoftAP auto channel select feature. \n
*     2.Optional: NULL. \n
*
* @note Support MT7682/Mt7686.
*/
#define WIFI_DEFAULT_AP_AUTO_CHANNEL_SELECT ("0")

/**@brief BcnDisEn, the value at SoftAP mode, the device used at startup. This flag was needed for feature Update homekit IE and enable /disable Airplay for specific customer.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: No. \n 
*
* @param[in] String: BcnDisEn \n
*     1.Default: 0, not support SoftAP beacon disable. \n
*     2.Optional: 1, support SoftAP beacon disable. \n
*
* @note Support MT5932/7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_AP_BEACON_DISABLE      ("0")


/**@brief xxx. the value at SoftAP mode, the device used at startup. These flags were defined for IOT's  MBSS feature.
*
*  Usage: #Not Support.  \n
*  Dependence: enable MTK_WIFI_CONFIGURE_FREE_ENABLE feature. \n 
*
* @param[in] String: xxx \n
*     1.Default: 0, enable MBSS. \n
*     2.Optional: 1, disable MBSS. \n
*
* @note Not Support.
*/
#define WIFI_DEFAULT_MBSS_ENABLE            ("0")

/**@brief xxx, the value at SoftAP mode, the device used at startup.
*
*  Usage: #Not Support.  \n
*  Dependence: enable MTK_WIFI_CONFIGURE_FREE_ENABLE feature. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK_MBSS1, default MBSS ssid1. \n
*     2.Optional: by user requirement. The maximum length is 32 bytes. \n
*
* @note Not Support.
*/
#define WIFI_DEFAULT_MBSS_SSID1             ("MTK_MBSS1")

/**@brief xxx, the value at SoftAP mode, the device used at startup.
*
*  Usage: #Not Support.  \n
*  Dependence: Feature MTK_WIFI_CONFIGURE_FREE_ENABLE. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK_MBSS2, default MBSS ssid2. \n
*     2.Optional: by user requirement. The maximum length is 32 bytes. \n
*
* @note Not Support.
*/
#define WIFI_DEFAULT_MBSS_SSID2             ("MTK_MBSS2")

#ifdef MTK_WIFI_WPS_ENABLE

/**@brief xxx. the value at WPS interaction, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_WPS_ENABLE. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK, default manufacturer. \n
*     2.Optional: by user requirement. The maximum length is #WIFI_WPS_MAX_LENGTH_MANUFACTURER in bytes. \n
*
* @note Support MT7682/7686/7698, MT7687/7697. 
*/
#define WIFI_DEFAULT_MANUFACTURER           ("MTK")

/**@brief xxx. the value at SoftAP mode, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_WPS_ENABLE. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK Wireless Device, default model name. \n
*     2.Optional: by user requirement. The maximum length is #WIFI_WPS_MAX_LENGTH_MODEL_NAME in bytes. \n
*
* @note Support MT7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_MODEL_NAME             ("MTK Wireless Device")

/**@brief xxx. the value at WPS interaction, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_WPS_ENABLE. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK Wireless Device, default model number. \n
*     2.Optional: by user requirement. The maximum length is #WIFI_WPS_MAX_LENGTH_MODEL_NUMBER in bytes. \n
*
* @note Support MT7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_MODEL_NUMBER           ("MT7687")

/**@brief xxx. the value at WPS interaction, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_WPS_ENABLE. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK Wireless Device, default model number. \n
*     2.Optional: by user requirement. The maximum length is #WIFI_WPS_MAX_LENGTH_SERIAL_NUMBER in bytes. \n
*
* @note Support MT7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_SERIAL_NUMBER          ("12345678")

/**@brief xxx. the value at WPS interaction, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_WPS_ENABLE. \n 
*
* @param[in] String: xxx \n
*     1.Default: MTK Wireless Device, default device name. \n
*     2.Optional: by user requirement. The maximum length is #WIFI_WPS_MAX_LENGTH_DEVICE_NAME in bytes. \n
*
* @note Support MT7682/7686/7698, MT7687/7697.
*/
#define WIFI_DEFAULT_DEVICE_NAME            ("MTK IoT")
#endif

#ifdef MTK_WIFI_CONFIGURE_FREE_ENABLE
/**@brief ConfigFree_Ready, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_CONFIGURE_FREE_ENABLE. \n 
*
* @param[in] String: ConfigFree_Ready \n
*     1.Default: 0, config_free is not ready. \n
*     2.Optional: 1, config_free is ready. \n
*
* @note Support MT7682.
*/
#define WIFI_DEFAULT_CONFIG_FREE_READY      ("0")

/**@brief ConfigFree_Enable, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_WIFI_CONFIGURE_FREE_ENABLE. \n 
*
* @param[in] String: ConfigFree_Enable \n
*     1.Default: 0, config_free is disable. \n
*     2.Optional: 1, config_free is enable. \n
*
* @note Support MT7682.
*/
#define WIFI_DEFAULT_CONFIG_FREE_ENABLE     ("0")
#endif

#ifdef MTK_WIFI_STA_CSA_ENABLE
/**@brief STACSAEnable, the value at station mode, the device used at startup.
*
*  Usage: #User_can_modify.  \n
*  Dependence: Fearure MTK_WIFI_STA_CSA_ENABLE . \n 
*
* @param[in] String: STACSAEnable \n
*     1.Default: 0, disable station mode CSA(Channel Switch Announcement) feature. \n
*     2.Optional: 1, enable station mode CSA feature.  \n
*
* @note Support MT7682/7686.
*/
#define WIFI_DEFAULT_STA_CSA_ENABLE         ("0")
#endif

#ifdef MTK_SINGLE_SKU_SUPPORT

/**@brief SupportSingleSKU, the supported SingleSKU type, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Feature MTK_SINGLE_SKU_SUPPORT. \n 
*
* @param[in] String: SupportSingleSKU \n
*     1.Default: 1,support 2G SKU. \n
*     2.Optional: 0~3, 0:not support single SKU, 1:support 2G SKU, 2:support 5G SKU, 3:support 2G and 5G SKU. \n
*
* @note Support MT7682/7686 for 2.4G, MT7687/7697 2.4G and 5G.
*/
#define WIFI_DEFAULT_SUPPORT_SINGLE_SKU ("1")    //0:not support single SKU, 1:support 2G SKU, 2:support 5G SKU, 3:support 2G and 5G SKU

//2G number is WIFI_2G_CHANNEL_NUMBER
#define WIFI_DEFAULT_SKU_2G_GROUP0  \
("15,15,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,16,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
17,17,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
19,19,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,15,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,16,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
17,17,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
19,19,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,15,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,16,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
17,17,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19")

//5G_L0 number is WIFI_5G_LOW_CHANNEL_NUMBER
#define WIFI_DEFAULT_SKU_5G_L0 \
"11,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
12,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
13,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
11,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
12,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
13,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
11,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
12,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
13,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
11,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
12,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
13,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
11,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
12,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19"

//5G_M0 number is WIFI_5G_MIDDLE_CHANNEL_NUMBER
#define WIFI_DEFAULT_SKU_5G_M0 \
"14,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
14,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
14,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
14,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
16,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
14,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
15,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19"

//5G_H0 number is WIFI_5G_HIGH_CHANNEL_NUMBER
#define WIFI_DEFAULT_SKU_5G_H0 \
"17,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
19,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
17,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
19,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
17,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
19,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
17,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19,\
18,18,18,18,18,17,17,17,17,17,17,19,19,19,19,19,19"


#define WIFI_DEFAULT_SKU_5G_GROUP0  (WIFI_DEFAULT_SKU_5G_L0","WIFI_DEFAULT_SKU_5G_M0","WIFI_DEFAULT_SKU_5G_H0)

#endif /*MTK_SINGLE_SKU_SUPPORT*/

#ifdef MTK_ANT_DIV_ENABLE
/**@brief AntennaNumber, the antenna number, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntennaNumber \n
*     1.Default: 0, antenna number. \n
*     2.Optional:1, Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_NUMBER             ("0")

/**@brief AntDiversityEnable, the RF diversity feature enable, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntDiversityEnable \n
*     1.Default: 0, disable antenna_diversity_enable. \n
*     2.Optional: 1, Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_DIVERSITY_ENABLE   ("0")

/**@brief AntProbeReqCount, the probe request count that will send for rssi collection from probe response from target AP, the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntProbeReqCount \n
*     1.Default: 3,  antenna probe request count. \n
*     2.Optional: Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_PROB_REQ_COUNT     ("3")

/**@brief AntThresholdRssi, the rssi threshold to trigger RF diversity algorithm when main antenna rssi less than threshold, it used \n
*             together with  #antenna_delta_rssi. the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntThresholdRssi \n
*     1.Default: -50,  antenna threshold level(dbm). \n
*     2.Optional: Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_THRESHOLD_LEVEL    ("-50")

/**@brief AntDeltaRssi, the delta rssi threshold to trigger RF diversity algorithm, when the diff between main antenna and #antenna_pre_selected_rssi \n 
*             is bigger than it, it used together with  #antenna_threshold_level. The device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntDeltaRssi \n
*     1.Default: 5,  antenna delta rssi(dbm). \n
*     2.Optional: Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_DELTA_RSSI         ("5")

/**@brief AntRssiSwitch, the rssi switch threshold, when the diff between aux antenna rssi and main antenna rssi is bigger than it, \n
*             the antenna will switch. the device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntRssiSwitch \n
*     1.Default: 5,  antenna rssi switch (dbm). \n
*     2.Optional: Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_RSSI_SWITCH        ("5")

/**@brief AntPreSelectedRssi, the rssi of the last time antenna was switched. The device used at startup.
*
*  Usage: #Confirm_with_Airoha.  \n
*  Dependence: Fearure MTK_ANT_DIV_ENABLE . \n 
*
* @param[in] String: AntPreSelectedRssi \n
*     1.Default: -110,  antenna previously selected rssi(dbm). \n
*     2.Optional: Please refer #wifi_rf_diversity for detail.  \n
*
* @note Support MT7697H. From c4sp.
*/
#define WIFI_DEFAULT_ANT_PRE_SELECTED_RSSI  ("-110")
#endif





/**@brief DataMaxRetryCount. the data frame max retry count
*
*  Usage: Confirm_with_Airoha.  \n
*  Dependence: None . \n
*
* @param[in] String: MaxRetryCount \n
*     1.Default: 15, the max retry count is 15(include the count of competition channe failed).\n
*     2.Optional: 1~31, if set to 31, will always retry transmint until sucssfuls.  \n
*
* @note Support MT7682/MT7686/MT5932/MT7698.
*/
#define WIFI_DEFAULT_MAX_RETRY_COUNT         ("15")

/**@brief STA channel switch according the CSA IE in Beacon frame that sent from current connected  AP
*
*  Usage: Confirm_with_Airoha.  \n
*  Dependence: None . \n
*
* @param[in]: STACSACfg \n
*     1. 0 - Disable STA channel switch according the CSA IE in Beacon frame. \n
*     2. 1 - Enable STA channel switch according the CSA IE in Beacon frame.  \n
*
* @note Support MT7682/MT7686/MT5932/MT7698.
*/
#define WIFI_DEFAULT_STA_CSA_CFG         ("0")



/**@brief STA and AP cca threshold value
*
*  Usage: Confirm_with_Airoha.  \n
*  Dependence: None . \n
*
* @param[in] String: CcaThreshold \n
*     1.Default: -65dbm.\n
*     2.Optional: [-126, 1]  if out of range, will use system defalut value(-65dbm)\n
*     As the real effect value is depend on the chip's capability, Please must confirm with Airoha's Hardware Engineer first before changing this setting.
*
* @note Support MT7682/MT7686/MT5932/MT7698.
*/
#define WIFI_DEFAULT_CCA_THRESHOLD        ("-65")


/**@brief STA control frame rate sets
*
*  Usage: Confirm_with_Airoha.  \n
*  Dependence: None . \n
*
* @param[in] String: CtlRateSets \n
*     1.Default: 351.\n
*     2.Optional: [17, 4095]   if out of range, will use system defalut value(351)\n
*     As the real effect value is depend on the chip's capability, Please must confirm with Airoha's Hardware Engineer first before changing this setting.
*
* @note Support MT7682/MT7686/MT5932/MT7698.
*/
#define WIFI_DEFAULT_STA_CTL_RATE_SETS      ("351")


/**
* @brief This function get Wi-Fi default configuration in hardcode.
*
* @param[in] syscfg is a pointer to the #wifi_sys_cfg_t. Read hardcode configuration saved in it.
*
* @return  >=0 the operation completed successfully, <0 the operation failed.
*/
int32_t wifi_get_default_config(wifi_sys_cfg_t *syscfg);


#ifdef __cplusplus
    }
#endif

/**
* @}
*/

#endif //__WIFI_DEFAULT_CONFIG_H__

