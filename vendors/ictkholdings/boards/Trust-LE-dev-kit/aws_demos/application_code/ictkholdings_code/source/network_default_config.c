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
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "os.h"

#include "nvdm.h"
#include "network_default_config.h"
#include "connsys_profile.h"
#include "get_profile_string.h"
#include "nvdm_config.h"

#ifdef __ICCARM__
#define STRCPY strncpy
#else
#define STRCPY strlcpy
#endif

static const group_data_item_t g_network_data_item_array[] = {
    NVDM_DATA_ITEM("IpAddr",          "192.167.1.1"),/*192.168.1.1*/
    NVDM_DATA_ITEM("IpNetmask",       "255.255.255.0"),
    NVDM_DATA_ITEM("IpGateway",       "192.168.1.254"),
    NVDM_DATA_ITEM("IpMode",          "dhcp"),
};

static void network_check_default_value(void)
{
    check_default_value("network",
                        g_network_data_item_array,
                        sizeof(g_network_data_item_array) / sizeof(g_network_data_item_array[0]));
}

static void network_reset_to_default(void)
{
    reset_to_default("network",
                     g_network_data_item_array,
                     sizeof(g_network_data_item_array) / sizeof(g_network_data_item_array[0]));
}

static void network_show_value(void)
{
    show_group_value("network",
                     g_network_data_item_array,
                     sizeof(g_network_data_item_array) / sizeof(g_network_data_item_array[0]));
}

const user_data_item_operate_t network_data_item_operate_array[] = {
    {
        "network",
        network_check_default_value,
        network_reset_to_default,
        network_show_value,
    },
};

#ifdef MTK_WIFI_PROFILE_ENABLE
int32_t dhcp_config_init(void)
{
    uint8_t buff[PROFILE_BUF_LEN] = {0};
    uint32_t sz = sizeof(buff);

    nvdm_read_data_item("network", "IpMode", buff, &sz);
    return strcmp((char *)buff, "dhcp") ? STA_IP_MODE_STATIC : STA_IP_MODE_DHCP;
}
int ap_init_tcpip_config(int check){
  uint8_t buff[PROFILE_BUF_LEN] = {0};
  uint32_t sz = sizeof(buff);
  //char* init_ip ="192.168.1.1";
  uint8_t ip_addr[4] = {0};
  uint8_t init_ip_address[] = {'1','9','2','.','1','6','8','.','1','.','1'};
  uint8_t default_ip_address[] = {'1','9','2','.','1','6','8','.','9','.','1'};
  if(check == 1){
    nvdm_read_data_item("network", "IpAddr", buff, &sz);
    if( os_memcmp( buff, init_ip_address, sz ) == 0 ){
      //for(int i = 0 ; i < sz ; i++)
      //  printf("[%02x %02x]",buff[i], init_ip_address[i]);
      nvdm_write_data_item("network", "IpAddr", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)default_ip_address, strlen((char *)default_ip_address));
      return 1;
    }else{
      return 0;
    }
  }else{  
    nvdm_write_data_item("network", "IpAddr", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)default_ip_address, strlen((char *)default_ip_address));
    return 1;
  }
}
void set_wifi_mode(const char* mode){
  int32_t ret = 0;
  uint32_t len = sizeof(mode);
  
  //nvdm_status_t status;
  //status = nvdm_write_data_item("common","OpMode", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)mode, len
  nvdm_write_data_item("common","OpMode", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)mode, len);
}
void set_init_ap_info(){
  char *Ssid="Trust-Fi";
  char *WpaPsk = "12345678";
  uint32_t len ;
  int8_t len2[5];

  len = strlen(Ssid);
  nvdm_write_data_item("AP", "Ssid", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)Ssid, len);
  sprintf(len2, "%d",len);
  nvdm_write_data_item("AP", "SsidLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));

  len = strlen(WpaPsk);
  nvdm_write_data_item("AP", "WpaPsk", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)WpaPsk, len);
  sprintf(len2, "%d",len);
  nvdm_write_data_item("AP", "WpaPskLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));
}
uint8_t get_wifi_mode(){
  uint8_t buff[10]; 
  uint32_t len = sizeof(buff);
  uint8_t opmode = 0;
  len = sizeof(buff);
  nvdm_read_data_item("common", "OpMode", buff, &len);
  opmode = (uint8_t)atoi(buff);
  return opmode;
}

int32_t tcpip_config_init(lwip_tcpip_config_t *tcpip_config)
{
    uint8_t ip_addr[4] = {0};
    uint8_t buff[PROFILE_BUF_LEN] = {0};
    uint32_t sz = sizeof(buff);
	  uint8_t default_ip_address[] = {'1','9','2','.','1','6','8','.','4','.','1'};
    uint8_t init_ip_address[] = {'1','9','2','.','1','6','8','.','1','.','1'};

    tcpip_config->ip_mode = dhcp_config_init();

    //nvdm_read_data_item("network", "IpAddr", buff, &sz);
	  //if( os_memcmp( buff, default_ip_address, sz ) != 0 ){
	  //if( os_memcmp( buff, init_ip_address, sizeof(init_ip_address) ) == 0 )
	  //if(is_Init_tcpip_config() == 1){
		//  nvdm_write_data_item("network", "IpAddr", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)default_ip_address, strlen((char *)default_ip_address));
		//  memset(buff, 0x00, sz);
	  //}   
    nvdm_read_data_item("network", "IpAddr", buff, &sz);
    wifi_conf_get_ip_from_str(ip_addr, (char *)buff);
    IP4_ADDR(&tcpip_config->sta_addr, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    IP4_ADDR(&tcpip_config->ap_addr, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    sz = sizeof(buff);
    nvdm_read_data_item("network", "IpNetmask", buff, &sz);
    wifi_conf_get_ip_from_str(ip_addr, (char *)buff);
    IP4_ADDR(&tcpip_config->sta_mask, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    IP4_ADDR(&tcpip_config->ap_mask, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    sz = sizeof(buff);
    nvdm_read_data_item("network", "IpGateway", buff, &sz);
    wifi_conf_get_ip_from_str(ip_addr, (char *)buff);
    IP4_ADDR(&tcpip_config->sta_gateway, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    IP4_ADDR(&tcpip_config->ap_gateway, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    return 0;
}

static uint32_t ip_number_to_big_endian(uint32_t ip_number)
{
    uint8_t *byte = (uint8_t *)&ip_number;
    return (uint32_t)((byte[0] << 24) | (byte[1] << 16) | (byte[2] << 8) | byte[3]);
}

static void ip_number_to_string(uint32_t ip_number, char ip_string[IP4ADDR_STRLEN_MAX])
{
    snprintf(ip_string,
             IP4ADDR_STRLEN_MAX,
             "%d.%d.%d.%d",
             (uint8_t)((ip_number >> 24) & 0xFF),
             (uint8_t)((ip_number >> 16) & 0xFF),
             (uint8_t)((ip_number >> 8) & 0xFF),
             (uint8_t)((ip_number >> 0) & 0xFF));
}

static void dhcpd_set_ip_pool(const ip4_addr_t *ap_ip_addr,
                              const ip4_addr_t *ap_net_mask,
                              char ip_pool_start[IP4ADDR_STRLEN_MAX],
                              char ip_pool_end[IP4ADDR_STRLEN_MAX])
{
    uint32_t ap_ip_number = ip_number_to_big_endian(ip4_addr_get_u32(ap_ip_addr));
    uint32_t ap_mask_number = ip_number_to_big_endian(ip4_addr_get_u32(ap_net_mask));
    uint32_t ip_range_min = ap_ip_number & ap_mask_number;
    uint32_t ip_range_max = ip_range_min | (~ap_mask_number);

    if ((ip_range_max - ap_ip_number) > (ap_ip_number - ip_range_min)) {
        ip_number_to_string(ap_ip_number + 1, ip_pool_start);
        ip_number_to_string(ip_range_max - 1, ip_pool_end);
    } else {
        ip_number_to_string(ip_range_min + 1, ip_pool_start);
        ip_number_to_string(ap_ip_number - 1, ip_pool_end);
    }
}

void dhcpd_settings_init(const lwip_tcpip_config_t *tcpip_config,
                         dhcpd_settings_t *dhcpd_settings)
{
    STRCPY(dhcpd_settings->dhcpd_server_address,
           ip4addr_ntoa(&tcpip_config->ap_addr),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_netmask,
           ip4addr_ntoa(&tcpip_config->ap_mask),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_gateway,
           (char *)dhcpd_settings->dhcpd_server_address,
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_primary_dns,
           (char *)dhcpd_settings->dhcpd_server_address,
           IP4ADDR_STRLEN_MAX);

    /* secondary DNS is not defined by default */
    STRCPY(dhcpd_settings->dhcpd_secondary_dns,
           "0.0.0.0",
           IP4ADDR_STRLEN_MAX);

    dhcpd_set_ip_pool(&tcpip_config->ap_addr,
                      &tcpip_config->ap_mask,
                      dhcpd_settings->dhcpd_ip_pool_start,
                      dhcpd_settings->dhcpd_ip_pool_end);
}

#else

int32_t dhcp_config_init(void)
{
    return (USE_DHCP == 0) ? STA_IP_MODE_STATIC : STA_IP_MODE_DHCP;
}

int32_t tcpip_config_init(lwip_tcpip_config_t *tcpip_config)
{
    tcpip_config->ip_mode = dhcp_config_init();

    ip4addr_aton(STA_IPADDR, &(tcpip_config->sta_addr));
    ip4addr_aton(STA_NETMASK, &tcpip_config->sta_mask);
    ip4addr_aton(STA_GATEWAY, &tcpip_config->sta_gateway);

    ip4addr_aton(AP_IPADDR, &(tcpip_config->ap_addr));
    ip4addr_aton(AP_NETMASK, &tcpip_config->ap_mask);
    ip4addr_aton(AP_GATEWAY, &tcpip_config->ap_gateway);

    return 0;
}

void dhcpd_settings_init(const lwip_tcpip_config_t *tcpip_config,
                         dhcpd_settings_t *dhcpd_settings)
{
    STRCPY(dhcpd_settings->dhcpd_server_address,
           ip4addr_ntoa(&tcpip_config->ap_addr),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_netmask,
           ip4addr_ntoa(&tcpip_config->ap_mask),
           IP4ADDR_STRLEN_MAX);

    STRCPY(dhcpd_settings->dhcpd_gateway,
           (char *)dhcpd_settings->dhcpd_server_address,
           IP4ADDR_STRLEN_MAX);

    strcpy((char *)dhcpd_settings->dhcpd_primary_dns,    PRIMARY_DNS);
    strcpy((char *)dhcpd_settings->dhcpd_secondary_dns,  SECONDARY_DNS);
    strcpy((char *)dhcpd_settings->dhcpd_ip_pool_start,  IP_POOL_START);
    strcpy((char *)dhcpd_settings->dhcpd_ip_pool_end,    IP_POOL_END);
}
#endif
