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
#include "g3_nvdm_config.h"
#endif
#include "aws_iot_mqtt_client.h"
#include "aws_iot.h"



log_create_module(ATCMD_AWS, PRINT_LEVEL_INFO);
#define LOGE(fmt,arg...)   LOG_E(ATCMD_AWS, "ATCI iot_sdk project: "fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(ATCMD_AWS, "ATCI iot_sdk project: "fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(ATCMD_AWS, "ATCI iot_sdk project: "fmt,##arg)


atci_status_t  atci_cmd_hdlr_ver(atci_parse_cmd_param_t *parse_cmd);

atci_status_t  atci_cmd_hdlr_aws_ep(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_pn(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_tn(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_cid(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_ac(atci_parse_cmd_param_t *parse_cmd);

atci_status_t  atci_cmd_hdlr_aws_connect(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_pub(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_sub(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_unsub(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_update(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_aws_delta(atci_parse_cmd_param_t *parse_cmd);




/*---  Variant ---*/
atci_cmd_hdlr_item_t aws_table[] = {
  {"AT+VER",          atci_cmd_hdlr_ver,            0, 0},  /* ZWG3M Version :    */

  {"AT+AWS_EP",       atci_cmd_hdlr_aws_ep,         0, 0},  /* AWS End Point :    */
  {"AT+AWS_PN",       atci_cmd_hdlr_aws_pn,         0, 0},  /* AWS Port Number :  */
  {"AT+AWS_TN",       atci_cmd_hdlr_aws_tn,         0, 0},  /* AWS Thing Name :   */
  {"AT+AWS_CID",      atci_cmd_hdlr_aws_cid,        0, 0},  /* AWS Client ID :    */
  {"AT+AWS_AC",       atci_cmd_hdlr_aws_ac,         0, 0},  /* AWS Auto-connect : */

  {"AT+AWS_CONN",     atci_cmd_hdlr_aws_connect,    0, 0},  /* AWS Connect :      */

  {"AT+AWS_PUB",      atci_cmd_hdlr_aws_pub,        0, 0},  /* AWS Publish :      */
  {"AT+AWS_SUB",      atci_cmd_hdlr_aws_sub,        0, 0},  /* AWS Subscirbe :    */
  {"AT+AWS_UNSUB",    atci_cmd_hdlr_aws_unsub,      0, 0},  /* AWS Unsubscirbe :  */
  {"AT+AWS_DELTA",    atci_cmd_hdlr_aws_delta,      0, 0},  /* AWS Delta :        */
  {"AT+AWS_UPDATE",   atci_cmd_hdlr_aws_update,     0, 0},  /* AWS Update :       */
};


///-----------------------------------------------------------------------------
atci_status_t atci_aws_init()
{
  atci_status_t ret = ATCI_STATUS_REGISTRATION_FAILURE;

  LOGW("atci_aws_init\r\n");

  ret = atci_register_handler(aws_table, sizeof(aws_table) / sizeof(atci_cmd_hdlr_item_t));
  if (ret == ATCI_STATUS_OK) {
    LOGW("atci_aws_init register success\r\n");
  } else {
    LOGW("atci_aws_init register fail\r\n");
  }

  return ret;
}


/*--- AT command handler ---*/
///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_ver(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t ac = 0;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);

  int32_t ret = 0;
  
  LOGI("atci_cmd_hdlr_ver");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) 
  {
    case ATCI_CMD_MODE_READ:    // rec: AT+VER?
      LOGI("AT Read done.\n");
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+VER:%s\n", ZRG3M_VER);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);    
      break;

    case ATCI_CMD_MODE_EXECUTION:
    case ATCI_CMD_MODE_TESTING: // rec: AT+VER=?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+VER
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
atci_status_t atci_cmd_hdlr_aws_ac(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t ac = 0;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);

  int32_t ret = 0;
  
  LOGI("atci_cmd_hdlr_aws_ac");
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
        ac = (uint8_t) atoi(param);
        

        if(ac > 1)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Range\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        }
        else
        {
          ret = nvdm_write_data_item("amazon", "Autoconn", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

          if (ret != 0) 
          {
            sprintf((char *)response.response_buf, "FAILED: Status=%d\n", ret);
            response.response_len = strlen((char *)response.response_buf);
            ret = 1;
          } else {
            sprintf((char *)response.response_buf, "SUCCEED\n");
            response.response_len = strlen((char *)response.response_buf);
            ret = 0;
          }
          LOGI("nvdm_write_data_item Status=%d, Autoconn=%s\n", ret, param);          


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

    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_AC?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      nvdm_read_data_item("amazon", "Autoconn", buff, &len);
      ac = (uint8_t) atoi((char *)buff);
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+AWS_AC:%d\n", ac);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);    
      break;


    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_AC=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_AC:[0|1]\n"); /// 1: Auto-connect, 0: Manual
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_AC
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
atci_status_t atci_cmd_hdlr_aws_connect(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint8_t conn = 0;

  uint32_t len;

  at2mqtt_msg_type msg;


  LOGI("atci_cmd_hdlr_aws_conn");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) {
    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_EXECUTION: 
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
     

      param = strtok(NULL, ",");
      conn = (uint32_t) atoi(param);
      if((param == NULL) || (conn > 1))
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide argument\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }

      if(xQueue_at2mqtt == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:xQueue_at2mqtt was not created\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      msg.cmd          = AT2MQTT_CMD_CONNECT;
      msg.connect.conn = conn;

      if(xQueueSend(xQueue_at2mqtt, (void*) &msg, (TickType_t) 10) != pdPASS)
      {
        sprintf((char *)response.response_buf, "FAILED:Sending Message\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        
        goto exit;
      }

      sprintf((char *)response.response_buf, "SUCCEED\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_CONN=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_CONN:[0|1]\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_CONN?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_CONN
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      break;

  }

exit:
  atci_send_response(&response);

  return ATCI_STATUS_OK;
}


///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_aws_ep(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);

  int32_t ret = 0;

  LOGI("atci_cmd_hdlr_aws_ep");
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

        if(len > NVDM_EP_LEN)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
          ret = nvdm_write_data_item("amazon", "Endpoint", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

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
          LOGI("nvdm_write_data_item Status=%d, Endpoint=%s\n", ret, param);          


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

    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_EP?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      nvdm_read_data_item("amazon", "Endpoint", buff, &len);
      /// Check len of buff(Endpoint)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+AWS_EP:%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);      
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_EP=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_EP:endpoint\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_EP
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
atci_status_t atci_cmd_hdlr_aws_pn(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  uint32_t pn = 0;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);

  int32_t ret = 0;
  
  LOGI("atci_cmd_hdlr_aws_pn");
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
        pn = (uint32_t) atol(param);
        

        if(pn > 65535)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Range\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
          ret = nvdm_write_data_item("amazon", "Portnum", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

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
          LOGI("nvdm_write_data_item Status=%d, Portnumber=%s\n", ret, param);          


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

    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_PN?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      nvdm_read_data_item("amazon", "Portnum", buff, &len);
      pn = (uint16_t) atoi((char *)buff);
      /// Check len of buff(Port Number: Limit 65535)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+AWS_PN:%d\n", pn);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);    
      break;


    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_PN=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_PN:portnumber\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_PN
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
atci_status_t atci_cmd_hdlr_aws_tn(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);

  int32_t ret = 0;

  LOGI("atci_cmd_hdlr_aws_tn");
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

        if(len > NVDM_TN_LEN)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
          ret = nvdm_write_data_item("amazon", "Thingname", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

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
          LOGI("nvdm_write_data_item Status=%d, Thingname=%s\n", ret, param);          


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


    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_TN?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      nvdm_read_data_item("amazon", "Thingname", buff, &len);
      /// Check len of buff(Thing Name)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+AWS_TN:%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);        
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_TN=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_TN:thingname\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;
      
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_TN
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
atci_status_t atci_cmd_hdlr_aws_cid(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;

  uint8_t buff[100]; /// More than length of endpoint
  uint32_t len = sizeof(buff);

  int32_t ret = 0;

  LOGI("atci_cmd_hdlr_aws_cid");
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

        if(len > NVDM_CID_LEN)
        {
          sprintf((char *)response.response_buf, "FAILED:Invalide Length\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;  // ATCI will help append "ERROR" at the end of resonse buffer
        }
        else
        {
          ret = nvdm_write_data_item("amazon", "ClientID", NVDM_DATA_ITEM_TYPE_STRING, (uint8_t *)param, len);

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
          LOGI("nvdm_write_data_item Status=%d, ClientID=%s\n", ret, param);          


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



    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_CID?
      LOGI("AT Read done.\n");
      len = sizeof(buff);
      nvdm_read_data_item("amazon", "ClientID", buff, &len);
      /// Check len of buff(Thing Name)
     
      snprintf((char *)response.response_buf, sizeof(response.response_buf), "+AWS_CID:%.*s\n", len, buff);
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);    
      break;


    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_CID=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_CID:clientID\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;  // ATCI will help append OK at the end of resonse buffer
      atci_send_response(&response);
      break;

    
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_CID
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
atci_status_t atci_cmd_hdlr_aws_pub(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  char *topic = NULL;
  uint8_t qos = 0;
  char* payload = NULL;

  uint32_t len;

  at2mqtt_msg_type msg;


  LOGI("atci_cmd_hdlr_aws_pub");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) {
    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
     

      topic = strtok(NULL, ",");
      len = strlen(topic);
      if((topic == NULL) || (len > MAX_SHADOW_TOPIC_LENGTH_BYTES))
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide Topic Length\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      param = strtok(NULL, ",");
      qos = (uint32_t) atoi(param);
      if((param == NULL) || (qos > QOS1)) /// QOS2 Not support now ???.
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide QOS\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }

      payload = strtok(NULL, "\r\n");
      len = strlen(payload);
      if((payload == NULL) || (len > MAX_SIZE_OF_PAYLOAD))
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide payload Length\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      if(xQueue_at2mqtt == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:xQueue_at2mqtt was not created\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      msg.cmd         = AT2MQTT_CMD_PUB;
      msg.pub.topic   = (char*) pvPortMalloc(strlen(topic) + 1);
      if(msg.pub.topic == NULL) 
      {
        sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }
      msg.pub.qos     = qos;
      msg.pub.payload = (char*) pvPortMalloc(strlen(payload) + 1);
      if(msg.pub.payload == NULL) 
      {
        vPortFree(msg.pub.topic);
        sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }

      strcpy(msg.pub.topic, topic);
      strcpy(msg.pub.payload, payload);

      if(xQueueSend(xQueue_at2mqtt, (void*) &msg, (TickType_t) 10) != pdPASS)
      {
        sprintf((char *)response.response_buf, "FAILED:Sending Message\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        
        vPortFree(msg.pub.payload);
        vPortFree(msg.pub.topic);
        goto exit;
      }

      sprintf((char *)response.response_buf, "SUCCEED\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_PUB=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_PUB:topic,qos,payload\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_PUB?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_PUB
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      break;
  }

exit:
  atci_send_response(&response);

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_aws_sub(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  char *topic = NULL;
  uint8_t qos = 0;

  uint32_t len;

  at2mqtt_msg_type msg;


  LOGI("atci_cmd_hdlr_aws_sub");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) {
    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_EXECUTION: 
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
     

      topic = strtok(NULL, ",");
      len   = strlen(topic);
      if((topic == NULL) || (len > MAX_SHADOW_TOPIC_LENGTH_BYTES))      
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide Topic Length\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      param = strtok(NULL, ",");
      qos = (uint32_t) atoi(param);
      if((param == NULL) || (qos > QOS1)) /// QOS2 Not support now ???.
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide QOS\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }


      if(xQueue_at2mqtt == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:xQueue_at2mqtt was not created\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      msg.cmd         = AT2MQTT_CMD_SUB;
      msg.sub.topic   = (char*) pvPortMalloc(strlen(topic) + 1);
      if(msg.sub.topic == NULL) 
      {
        sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }
      msg.sub.qos     = qos;

      strcpy(msg.sub.topic, topic);

      if(xQueueSend(xQueue_at2mqtt, (void*) &msg, (TickType_t) 10) != pdPASS)
      {
        sprintf((char *)response.response_buf, "FAILED:Sending Message\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        
        vPortFree(msg.sub.topic);
        goto exit;
      }

      sprintf((char *)response.response_buf, "SUCCEED\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_SUB=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_SUB:topic,qos\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_SUB?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_SUB
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      break;

  }

exit:
  atci_send_response(&response);

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_aws_unsub(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  char *topic = NULL;

  uint32_t len;

  at2mqtt_msg_type msg;


  LOGI("atci_cmd_hdlr_aws_unsub");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) {
    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_EXECUTION: 
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");
     

      topic = strtok(NULL, "\r\n");
      len   = strlen(topic);
      if((topic == NULL) || (len > MAX_SHADOW_TOPIC_LENGTH_BYTES))        
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide Topic Length\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      if(xQueue_at2mqtt == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:xQueue_at2mqtt was not created\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      msg.cmd         = AT2MQTT_CMD_UNSUB;
      msg.unsub.topic = (char*) pvPortMalloc(strlen(topic) + 1);
      if(msg.unsub.topic == NULL) 
      {
        sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }


      strcpy(msg.unsub.topic, topic);

      if(xQueueSend(xQueue_at2mqtt, (void*) &msg, (TickType_t) 10) != pdPASS)
      {
        sprintf((char *)response.response_buf, "FAILED:Sending Message\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        
        vPortFree(msg.sub.topic);
        goto exit;
      }

      sprintf((char *)response.response_buf, "SUCCEED\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_UNSUB=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_UNSUB:topic\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_UNSUB?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_UNSUB
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      break;

  }

exit:
  atci_send_response(&response);

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_aws_update(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  char *key = NULL;

  act_type act;
  JsonPrimitiveType type;
  char* value = NULL;


  int32_t i32;
  int64_t i64;
  float   f32;

  uint32_t len;

  at2mqtt_msg_type msg;


  LOGI("atci_cmd_hdlr_aws_update");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) {
    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");


      if(xQueue_at2mqtt == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:xQueue_at2mqtt was not created\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }
     
      param = strtok(NULL, ",");
      act = (act_type) atoi(param);
      if((param == NULL) || (act >= ACT_MAX))
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide act type\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }

      key = strtok(NULL, ",");
      len = strlen(key);
      if((param == NULL) || (len > MAX_SIZE_OF_KEY))
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide key Length\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }

      param = strtok(NULL, ",");
      if(param == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide json type\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }
      type = (JsonPrimitiveType) atoi(param);

      msg.cmd         = AT2MQTT_CMD_UPDATE;
      msg.update.act  = act;
      msg.update.type = type;

      switch(type)
      {
        //--- signed int 32 ----------------------------------------------------
        case SHADOW_JSON_INT32:
          value = strtok(NULL, "\r\n");
          i64 = atol(value);

          if((value == NULL) || (i64 > LIMIT_I32_MAX) || (i64 < LIMIT_I32_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }

          msg.update.value.i32 = (int32_t) i64;
          break;

        //--- signed int 16 ----------------------------------------------------
        case SHADOW_JSON_INT16:
          value = strtok(NULL, "\r\n");
          i32 = atoi(value);

          if((value == NULL) || (i32 > LIMIT_I16_MAX) || (i32 < LIMIT_I16_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }

          msg.update.value.i16 = (int16_t) i32;
          break;

        //--- signed int 8 -----------------------------------------------------
        case SHADOW_JSON_INT8:
          value = strtok(NULL, "\r\n");
          i32 = atoi(value);

          if((value == NULL) || (i32 > LIMIT_I8_MAX) || (i32 < LIMIT_I8_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }
          msg.update.value.i8 = (int8_t) i32;
          break;

        //--- unsigned int 32 --------------------------------------------------
        case SHADOW_JSON_UINT32:
          value = strtok(NULL, "\r\n");
          i64 = atol(value);

          if((value == NULL) || (i64 > LIMIT_U32_MAX) || (i64 < LIMIT_U32_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }
          msg.update.value.ui32 = (uint32_t) i64;
          break;

        //--- unsigned int 16 --------------------------------------------------
        case SHADOW_JSON_UINT16:
          value = strtok(NULL, "\r\n");
          i32 = atoi(value);

          if((value == NULL) || (i32 > LIMIT_U16_MAX) || (i32 < LIMIT_U16_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }
          msg.update.value.ui16 = (uint16_t) i32;
          break;

        //--- unsigned int 8 ---------------------------------------------------
        case SHADOW_JSON_UINT8:
          value = strtok(NULL, "\r\n");
          i32 = atoi(value);

          if((value == NULL) || (i32 > LIMIT_U8_MAX) || (i32 < LIMIT_U8_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }
          msg.update.value.ui8 = (uint8_t) i32;
          break;

        //--- float 32 ---------------------------------------------------------
        case SHADOW_JSON_FLOAT:
          value = strtok(NULL, "\r\n");
          f32 = atof(value);

          if(value == NULL)
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }
          msg.update.value.f32 = (float) f32;
          break;

        //--- float 32 ---------------------------------------------------------
        case SHADOW_JSON_BOOL:
          value = strtok(NULL, "\r\n");
          i32 = atoi(value);

          if((value == NULL) || (i32 > LIMIT_B1_MAX) || (i32 < LIMIT_B1_MIN))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide type data\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }
          msg.update.value.b1 = (bool) i32;
          break;

        //--- float 32 ---------------------------------------------------------
        case SHADOW_JSON_STRING:
          value = strtok(NULL, "\r\n");
          len = strlen(value);

          if((value == NULL) || (len > MAX_SIZE_OF_VALUE))
          {
            sprintf((char *)response.response_buf, "FAILED:Invalide value length\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
            goto exit;
          }

          msg.update.value.str = (char*) pvPortMalloc(strlen(value) + 1);
          if(msg.update.value.str == NULL) 
          {
            sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
            response.response_len = strlen((char *)response.response_buf);
            response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
            goto exit;
          }
          strcpy(msg.update.value.str, value);
          break;

        //--- Not Support ------------------------------------------------------
        case SHADOW_JSON_DOUBLE:
        case SHADOW_JSON_OBJECT:
        default:
          sprintf((char *)response.response_buf, "FAILED:Invalide json type\n");
          response.response_len = strlen((char *)response.response_buf);
          response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
          goto exit;
      }

      msg.update.key  = (char*) pvPortMalloc(strlen(key) + 1);
      if(msg.update.key == NULL) 
      {
        vPortFree(msg.update.value.str);
        sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }
      strcpy(msg.update.key, key); 


      if(xQueueSend(xQueue_at2mqtt, (void*) &msg, (TickType_t) 10) != pdPASS)
      {
        sprintf((char *)response.response_buf, "FAILED:Sending Message\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        
        vPortFree(msg.update.key);
        vPortFree(msg.update.value.str);
        if(msg.update.type == SHADOW_JSON_STRING)
          vPortFree(msg.update.value.str);
        
        goto exit;
      }


      sprintf((char *)response.response_buf, "SUCCEED\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_UPDATE=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_UPDATE:act,key,type,value\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_UPDATE?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_UPDATE
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      break;
  }

exit:
  atci_send_response(&response);

  return ATCI_STATUS_OK;
}

///-----------------------------------------------------------------------------
atci_status_t atci_cmd_hdlr_aws_delta(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t response;
  char *param = NULL;
  char *key = NULL;

  act_type act;
  JsonPrimitiveType type;
  char* value = NULL;


  int32_t i32;
  int64_t i64;
  float   f32;

  uint32_t len;

  at2mqtt_msg_type msg;


  LOGI("atci_cmd_hdlr_aws_delta");
  os_memset(&response, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) {
    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      //parsing the parameter
      param = strtok(parse_cmd->string_ptr, "=");


      if(xQueue_at2mqtt == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:xQueue_at2mqtt was not created\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }
     
      key = strtok(NULL, ",");
      len = strlen(key);
      if((param == NULL) || (len > MAX_SIZE_OF_KEY))
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide key Length\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }

      param = strtok(NULL, ",");
      if(param == NULL)
      {
        sprintf((char *)response.response_buf, "FAILED:Invalide json type\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        goto exit;
      }
      type = (JsonPrimitiveType) atoi(param);

      msg.cmd        = AT2MQTT_CMD_DELTA;
      msg.delta.type = type;
      msg.delta.key  = (char*) pvPortMalloc(strlen(key) + 1);
      if(msg.delta.key == NULL) 
      {
        sprintf((char *)response.response_buf, "FAILED:malloc failed\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;         
        goto exit;
      }
      strcpy(msg.delta.key, key); 


      if(xQueueSend(xQueue_at2mqtt, (void*) &msg, (TickType_t) 10) != pdPASS)
      {
        sprintf((char *)response.response_buf, "FAILED:Sending Message\n");
        response.response_len = strlen((char *)response.response_buf);
        response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_ERROR;
        
        vPortFree(msg.delta.key);
        goto exit;
      }

      sprintf((char *)response.response_buf, "SUCCEED\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_TESTING: // rec: AT+AWS_DELTA=?
      LOGI("AT Test OK.\n");    
      strcpy((char *)response.response_buf, "+AWS_DELTA:key,type\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag |= ATCI_RESPONSE_FLAG_APPEND_OK;
      break;

    ///-------------------------------------------------------------------------
    case ATCI_CMD_MODE_READ:    // rec: AT+AWS_DELTA?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+AWS_DELTA
    default:
      strcpy((char *)response.response_buf, "Not Support\n");
      response.response_len = strlen((char *)response.response_buf);
      response.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      break;
  }

exit:
  atci_send_response(&response);

  return ATCI_STATUS_OK;
}


///-----------------------------------------------------------------------------

#endif /* ATCI_AWS_COMMAND_ENABLE */
