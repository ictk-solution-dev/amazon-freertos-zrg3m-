/* Copyright Statement:
 *
 * (C) 2019-2019  ICTK Inc.
 */


#ifdef ATCI_AWS_COMMAND_ENABLE
/* Includes ------------------------------------------------------------------*/
/*--- For Register AT command handler ---*/
#include "atci.h"
// System header files
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "os.h"
#include "os_util.h"
#include "syslog.h"
#include "misc.h"
#include "type_def.h"
#ifdef MTK_NVDM_ENABLE
#include "nvdm.h"
#include "wifi_nvdm_config.h"
#include "dhcp.h"
#include "ethernetif.h"
#include "wifi_lwip_helper.h"


#endif

log_create_module(ATCMD_WIFI, PRINT_LEVEL_INFO);
#define LOGE(fmt,arg...)   LOG_E(ATCMD_WIFI, "ATCI iot_sdk project: "fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(ATCMD_WIFI, "ATCI iot_sdk project: "fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(ATCMD_WIFI, "ATCI iot_sdk project: "fmt,##arg)


atci_status_t  atci_cmd_hdlr_wifi_ssid_sta(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_ssid_sta_u(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_ssid_ap(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_pw_sta(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_pw_ap(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_mac_sta(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_mac_ap(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_mode(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_country(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_region(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_ip_sta(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_ip_ap(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_secsta(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_secap(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_on(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_wifi_off(atci_parse_cmd_param_t *parse_cmd);

static void atci_cmd_show_ip(netif_type_t type);

/*---  Variant ---*/
atci_cmd_hdlr_item_t wifi_table[] = {
  {"AT+WIFI_SSID_STA",    atci_cmd_hdlr_wifi_ssid_sta,    0, 0},    /* WIFI SSID STA:  */  
  {"AT+WIFI_SSID_STA_U",  atci_cmd_hdlr_wifi_ssid_sta_u,  0, 0},    /* WIFI SSID STA:  */
  {"AT+WIFI_SSID_AP",     atci_cmd_hdlr_wifi_ssid_ap,     0, 0},    /* WIFI SSID AP :  */
  {"AT+WIFI_PW_STA",      atci_cmd_hdlr_wifi_pw_sta,      0, 0},    /* WIFI PW STA*/         
  {"AT+WIFI_PW_AP",       atci_cmd_hdlr_wifi_pw_ap,       0, 0},    /* WIFI PW AP */            
  {"AT+WIFI_MAC_STA",     atci_cmd_hdlr_wifi_mac_sta,     0, 0},    /* WIFI MAC ADDRESS STA */
  {"AT+WIFI_MAC_AP",      atci_cmd_hdlr_wifi_mac_ap,      0, 0},    /* WIFI MAC ADDRESS AP */
  {"AT+WIFI_MODE",        atci_cmd_hdlr_wifi_mode,        0, 0},    /* WIFI MODE  */    
  {"AT+WIFI_COUNTRY",     atci_cmd_hdlr_wifi_country,     0, 0},    /* WIFI COUNTRY : */
  {"AT+WIFI_REGION",      atci_cmd_hdlr_wifi_region,      0, 0},    /* WIFI REGION : */
  {"AT+WIFI_IP_STA",      atci_cmd_hdlr_wifi_ip_sta,      0, 0},    /* WIFI IP STA: */
  {"AT+WIFI_IP_AP",       atci_cmd_hdlr_wifi_ip_ap,       0, 0},    /* WIFI IP AP */
  {"AT+WIFI_SECMODE_STA", atci_cmd_hdlr_wifi_secsta,      0, 0},    /* WIFI SECURITY MODE STA : */
  {"AT+WIFI_SECMODE_AP",  atci_cmd_hdlr_wifi_secap,       0, 0},    /* WIFI SECURITY MODE AP: */
    
  {"AT+LWIP_ON",          atci_cmd_hdlr_wifi_on,          0, 0},    /* LWIP ON  : */
  {"AT+LWIP_OFF",         atci_cmd_hdlr_wifi_off,         0, 0},    /* LWIP OFF : */
};

static uint32_t hexstring_to_bytearray(char *s, uint8_t *bits)
{
    uint32_t i, n = 0;

    for (i = 0; s[i]; i += 2) {
        if (s[i] >= 'A' && s[i] <= 'F') {
            bits[n] = s[i] - 'A' + 10;
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            bits[n] = s[i] - 'a' + 10;
        } else {
            bits[n] = s[i] - '0';
        }
        if (s[i + 1] >= 'A' && s[i + 1] <= 'F') {
            bits[n] = (bits[n] << 4) | (s[i + 1] - 'A' + 10);
        } else if (s[i + 1] >= 'a' && s[i + 1] <= 'f') {
            bits[n] = (bits[n] << 4) | (s[i + 1] - 'a' + 10);
        } else {
            bits[n] = (bits[n] << 4) | (s[i + 1] - '0');
        }
        ++n;
    }

    return n;
}

///-----------------------------------------------------------------------------
atci_status_t atci_wifi_init()
{
  atci_status_t ret = ATCI_STATUS_REGISTRATION_FAILURE;

  LOGW("atci_wifi_init\r\n");

  ret = atci_register_handler(wifi_table, sizeof(wifi_table) / sizeof(atci_cmd_hdlr_item_t));
  if (ret == ATCI_STATUS_OK) {
    LOGW("atci_wifi_init register success\r\n");
  } else {
    LOGW("atci_wifi_init register fail\r\n");
  }

  return ret;
}


/*--- AT command handler ---*/
///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_wifi_ssid_sta(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  int8_t len2[5];

  LOGI("atci_cmd_hdlr_wifi_ssid_sta");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);

        if(len > 32)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
           ret = nvdm_write_data_item("STA", "Ssid", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);
           sprintf(len2, "%d",len);
           ret = nvdm_write_data_item("STA", "SsidLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, ssid =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
          nvdm_read_data_item("STA", "Ssid", buff, &len);
      
      /// Check len of buff(Endpoint)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_SSID_STA: %.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_SSID_STA: enter ssid \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_ssid_sta_u(atci_parse_cmd_param_t *parse_cmd)
{
   atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  int8_t len2[5];

  LOGI("atci_cmd_hdlr_wifi_ssid_sta");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);

                len = strlen(param);
                uint8_t ssid_str[50];
                hexstring_to_bytearray(param, ssid_str);

                for (uint8_t i = 0; i < len/2; i++) {
                        LOGI("%x", ssid_str[i]);
                    }
                len=len/2;
        //uint8_t ssid_str2[] = {0xec, 0xa7,0x80,0xec,0x97,0x94};
        len=6;
        if(len > 32)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
           ret = nvdm_write_data_item("STA", "Ssid", NVDM_DATA_ITEM_TYPE_STRING, ssid_str, len);
           sprintf(len2, "%d",len);
           ret = nvdm_write_data_item("STA", "SsidLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, ssid =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
          nvdm_read_data_item("STA", "Ssid", buff, &len);
      
      /// Check len of buff(Endpoint)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_SSID_STA: %.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_SSID_STA: enter ssid \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}

atci_status_t atci_cmd_hdlr_wifi_ssid_ap(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  int8_t len2[5];

  LOGI("atci_cmd_hdlr_wifi_ssid_ap");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);

        if(len > 33)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
           ret = nvdm_write_data_item("AP", "Ssid", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);
           sprintf(len2, "%d",len);
           ret = nvdm_write_data_item("AP", "SsidLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, ssid =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
     }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
          nvdm_read_data_item("AP", "Ssid", buff, &len);
      
      /// Check len of buff(Endpoint)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_SSID_AP: %.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_SSID_AP= enter ssid \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_wifi_pw_sta(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  //char *parami = NULL;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  int8_t len2[5];

  LOGI("atci_cmd_hdlr_wifi_pw_sta");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);

        if(len < 8 || len>32)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
           ret = nvdm_write_data_item("STA", "WpaPsk", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);
           sprintf(len2, "%d",len);
           ret = nvdm_write_data_item("STA", "WpaPskLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, pw  =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      //read passphrase from nv 
      nvdm_read_data_item("STA", "WpaPsk", buff, &len);

           
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_PW_STA: %.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_PW_STA=[passphrase] \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}

atci_status_t atci_cmd_hdlr_wifi_pw_ap(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  int8_t len2[5];
  

  LOGI("atci_cmd_hdlr_wifi_pw_ap");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);
        if(len < 8 || len>32)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
           ret = nvdm_write_data_item("AP", "WpaPsk", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);
           sprintf(len2, "%d",len);
           ret = nvdm_write_data_item("AP", "WpaPskLen", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)len2, strlen(len2));

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, pw =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
         nvdm_read_data_item("AP", "WpaPsk", buff, &len);
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_PW_AP: %.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "++WIFI_PW_AP=[passphrase] \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_mac_sta(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[30]; 
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  

  LOGI("atci_cmd_hdlr_wifi_mac_sta");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
           len = strlen(param);
           if(len> 18)
           {
             sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
             response.response_len = strlen((char *)response.response_buf);
             response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
           }
           else
           {
      
           ret = nvdm_write_data_item("STA", "MacAddr", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);
           
          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, macaddress =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
           }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_MAC _STA?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
         nvdm_read_data_item("STA", "MacAddr", buff, &len);

      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_MAC_STA:%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_MAC_STA=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_MAC_STA= [mac address] \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_MAC_STA
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_mac_ap(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[30]; 
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  

  LOGI("atci_cmd_hdlr_wifi_mac_ap");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);
           if(len> 18)
           {
             sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
             response.response_len = strlen((char *)response.response_buf);
             response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
           }
           else
           {
           ret = nvdm_write_data_item("AP", "MacAddr", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, macaddress =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_MAC_AP?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
         nvdm_read_data_item("AP", "MacAddr", buff, &len);

      
      /// Check len of buff(Endpoint)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_MAC:AP%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_MAC_AP=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_MAC_AP= macAddress \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_MAC_AP
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}




///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_wifi_mode(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;

  uint8_t buff[10]; 
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
    uint8_t opmode = 0;

  LOGI("atci_cmd_hdlr_wifi_opmode");
  os_memset(&response, 0, sizeof(atci_response_t));

  

  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");
      opmode = (uint8_t)atoi(param);

      

      if(param != NULL)
      {
        len = strlen(param);

        if(opmode > 3 || opmode<=0)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide input\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
           ret = nvdm_write_data_item("common", "OpMode", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, WIFI mode =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
        }
       }
      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIF_MAC?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      nvdm_read_data_item("common", "OpMode", buff, &len);
      opmode = (uint8_t)atoi(buff);

      
      /// Check len of buff(Endpoint)
     if (opmode==1)
     {
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_MODE: STA \n");
     }
     else  if (opmode==2)
     {
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_MODE: AP \n");
     }
     else
      {snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_MODE: RPT \n");
     }
      
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
    
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIF_MAC=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_MODE= 1,2,3 (1= STA,2=AP,3=RPT) \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIF_MAC
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_country(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  //char *parami = NULL;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  

  LOGI("atci_cmd_hdlr_wifi_country");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);

           ret = nvdm_write_data_item("common", "CountryCode", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, country =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
       // }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
         nvdm_read_data_item("common", "CountryCode", buff, &len);

      
      /// Check len of buff(Endpoint)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_COUNTRY:%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_COUNTRY=countrycode \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_region(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  

  LOGI("atci_cmd_hdlr_wifi_region");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");

      if(param != NULL)
      {
        len = strlen(param);

           ret = nvdm_write_data_item("common", "CountryRegion", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%ld\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, CountryRegion =%s\n", ret, param);          


          if (0 == ret) {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK; // ATCI will help append "OK" at the end of resonse buffer
          } else {
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR; // ATCI will help append "ERROR" at the end of resonse buffer
          }
       // }
      }

      atci_send_response(&response);
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_REGION?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
         nvdm_read_data_item("common", "CountryRegion", buff, &len);
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_region:%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_region=[region], default =5  \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // 
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_ip_sta(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  

  LOGI("atci_cmd_hdlr_wifi_ip");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    
     case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");

      atci_cmd_show_ip(NETIF_TYPE_STA);
       break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_IP_STA : Read only \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
    case ATCI_CMD_MODE_EXECUTION: 
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_ip_ap(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  int32_t ret = 0;
  

  LOGI("atci_cmd_hdlr_wifi_ip");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    
     case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SSID?
      LOGI("AT Read done.\n");

      atci_cmd_show_ip(NETIF_TYPE_AP);
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+WIFI_IP_AP: Read only \n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
    case ATCI_CMD_MODE_EXECUTION: 
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}

static void atci_cmd_show_ip(netif_type_t type)
{
    atci_response_t resonse = {{0}};
    char ip[16] = {0};
    char netmask[16] = {0};
    char gw[16] = {0};
    resonse.response_flag = 0; // Command Execute Finish.
    resonse.response_len  = 0;

    LOGI("show_ip:port=%d\n", type);
    struct netif *iface = netif_find_by_type(type);
    if (!iface) {
        sprintf((char *)resonse.response_buf, "Can't find interface by type. %d\n", type);
        resonse.response_len = strlen((char *)resonse.response_buf);
        atci_send_response(&resonse);
        return;
    }

#if LWIP_DHCP
    if (dhcp_supplied_address(iface)) {
        struct dhcp *d = iface->dhcp;
        strcpy(ip, ip4addr_ntoa(&d->offered_ip_addr));
        strcpy(netmask, ip4addr_ntoa(&d->offered_sn_mask));
        strcpy(gw, ip4addr_ntoa(&d->offered_gw_addr));
        sprintf((char *)resonse.response_buf, "mode:dhcp\r\nip:%s, netmask:%s, gateway:%s\n", ip, netmask, gw);
        resonse.response_len = strlen((char *)resonse.response_buf);
    } else
#endif
    {
        strcpy(ip, ip4addr_ntoa(&iface->ip_addr));
        strcpy(netmask, ip4addr_ntoa(&iface->netmask));
        strcpy(gw, ip4addr_ntoa(&iface->gw));
        sprintf((char *)resonse.response_buf, "mode:static\r\nip:%s, netmask:%s, gateway:%s\n", ip, netmask, gw);
        resonse.response_len = strlen((char *)resonse.response_buf);
    }
    atci_send_response(&resonse);
}
atci_status_t atci_cmd_hdlr_wifi_secsta(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  uint8_t length = 0;
  uint8_t ssid[32] = {0};
  uint8_t auth = 0;
  uint8_t encrypt = 0;
  uint8_t password[64] = {0};
  uint8_t ret = 0;


  LOGI("atci_cmd_hdlr_wifi_secsta");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) 
  {
    case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SECU_MODE?
      LOGI("AT Read done.\n");
      ret = wifi_config_get_ssid(WIFI_PORT_STA, ssid, &length);
      if (ret < 0)
      {
        LOGE("Get auth mode/encrypt type failed\n");
        ret = 1;
      }
      ret = wifi_config_get_security_mode(WIFI_PORT_STA, (wifi_auth_mode_t *)&auth, (wifi_encrypt_type_t *)&encrypt);
      if (ret < 0) {
        LOGE("Get auth mode/encrypt type failed\n");
        ret = 1;
      }

      sprintf((char *)response.response_buf, " [ssid]: %s, [Auth_Mode]: %d,[encrypt_type]: %d\n", ssid, auth, encrypt);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      /// Check len of buff(Endpoint)
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SSID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, " 0 open, AUTH MODE: 0 open, 4 WPA-PSK, 7 WPA2-PSK, 9 WPA-PSK/WPA-PSK2\n ENC TYPE: 0 WEP, 1 WEP, 4 TKIP, 6 AES, 8 TKIP/AES\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_EXECUTION: 
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
atci_status_t atci_cmd_hdlr_wifi_secap(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  uint8_t length = 0;
  uint8_t ssid[32] = {0};
  uint8_t auth = 0;
  uint8_t encrypt = 0;
  uint8_t password[64] = {0};
  uint8_t ret = 0;


  LOGI("atci_cmd_hdlr_wifi_secap");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  switch (parse_cmd->mode) {
    
     case ATCI_CMD_MODE_READ:    // rec: AT+WIFI_SECU_MODE_AP?
      LOGI("AT Read done.\n");
      ret = wifi_config_get_ssid(WIFI_PORT_AP, ssid, &length);
        if (ret < 0)
         {
              LOGE("Get auth mode/encrypt type failed\n");
              ret = 1;
         }
       ret = wifi_config_get_security_mode(WIFI_PORT_AP, (wifi_auth_mode_t *)&auth, (wifi_encrypt_type_t *)&encrypt);
      if (ret < 0) {
             LOGE("Get auth mode/encrypt type failed\n");
             ret = 1;
      }

      sprintf((char *)response.response_buf, "[ssid]: %s, [Auth_Mode]: %d,[encrypt_type]: %d\n ", ssid, auth, encrypt);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+WIFI_SECU_MODE_AP=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, " 0 open, AUTH MODE: 0 open, 4 WPA-PSK, 7 WPA2-PSK, 9 WPA-PSK/WPA-PSK2\n ENC TYPE: 0 WEP, 1 WEP, 4 TKIP, 6 AES, 8 TKIP/AES\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
    case ATCI_CMD_MODE_EXECUTION: 
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+WIFI_SSID
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_wifi_on(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;

  LOGI("atci_cmd_hdlr_wifi_on");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  uint8_t buff=0; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  
  int32_t ret = 0;
  //nvdm_read_data_item("common", "opmode", buff, &len);
  ret= wifi_config_get_opmode(&buff);

  switch (parse_cmd->mode) {
      case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_PUB

      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      param = strtok((char *)parse_cmd->string_ptr, "\r\n");
   
     lwip_net_start(buff);
     
      if (1 == buff) {
          ret = wifi_config_reload_setting();
      }
      
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_ON:%d\n", buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      

      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    
    case ATCI_CMD_MODE_TESTING: 
    case ATCI_CMD_MODE_EXECUTION:

    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_wifi_off(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;

  LOGI("atci_cmd_hdlr_wifi_on");
  os_memset(&response, 0, sizeof(atci_response_t));

  
  uint8_t buff=0; /// More than length of endpoint
  uint32_t len = sizeof(buff);
  
  int32_t ret = 0;
  //nvdm_read_data_item("common", "opmode", buff, &len);
  ret= wifi_config_get_opmode(&buff);

  switch (parse_cmd->mode) {
      case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_PUB

      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      param = strtok((char *)parse_cmd->string_ptr, "\r\n");

      lwip_net_stop(buff);

      if (ret < 0) {
          LOGE("Set opmode failed\n");
          ret = 1;
      } 
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+WIFI_OFF:%d\n",  buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      param = NULL;
      break;

    case ATCI_CMD_MODE_READ:    
    case ATCI_CMD_MODE_TESTING: 
    case ATCI_CMD_MODE_EXECUTION:

    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&response);
      break;
  }

  return ATCI_STATUS_OK;
}
///-----------------------------------------------------------------------------

#endif /* ATCI_AWS_COMMAND_ENABLE */
