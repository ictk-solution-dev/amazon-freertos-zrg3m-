/* Copyright Statement:
 *
 * (C) 2019-2019  ICTK Inc.
 */


#ifdef ATCI_ICTK_COMMAND_ENABLE
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
#endif
#include "mbedtls/x509_crt.h"

#include "common/util.h"
#include "g3_command.h"
#include "ictk/profile.h"
log_create_module(ATCMD_G3, PRINT_LEVEL_INFO);
#define LOGE(fmt,arg...)   LOG_E(ATCMD_G3, "ATCI iot_sdk project: "fmt,##arg)
#define LOGW(fmt,arg...)   LOG_W(ATCMD_G3, "ATCI iot_sdk project: "fmt,##arg)
#define LOGI(fmt,arg...)   LOG_I(ATCMD_G3, "ATCI iot_sdk project: "fmt,##arg)


/*void byteArray2String(uint8_t* input, char* output)
{
    int loop;
    int i;
    
    loop = 0;
    i = 0;
    
    while(input[loop] != '\0')
    {
        output[i++] = input[loop++];
    }
}*/

atci_status_t  atci_cmd_hdlr_g3(atci_parse_cmd_param_t *parse_cmd);
atci_status_t  atci_cmd_hdlr_g3_profile(atci_parse_cmd_param_t *parse_cmd);


/*---  Variant ---*/
atci_cmd_hdlr_item_t g3_table[] = {
    {"AT+G3",      atci_cmd_hdlr_g3,      0, 0},    
    {"AT+G3_PROFILE",      atci_cmd_hdlr_g3_profile,      0, 0},
};


atci_status_t atci_g3_init()
{
    atci_status_t ret = ATCI_STATUS_REGISTRATION_FAILURE;

    LOGW("atci_g3_init\r\n");

    ret = atci_register_handler(g3_table, sizeof(g3_table) / sizeof(atci_cmd_hdlr_item_t));
    if (ret == ATCI_STATUS_OK) {
        LOGW("atci_g3_init register success\r\n");
    } else {
        LOGW("atci_g3_init register fail\r\n");
    }

    return ret;
}
int eli_crlf(char *str, char* des)
{
	int i = 0;
    while(*str != '\0')
    {
        if (*str != '\r' || *str != '\n')//ch와 같은 문자일 때
        {
			str++;
			i++;
        }else{
			break;
        }
			
    }
	strncpy(des, str, i);
	return i;
}

int HexStringToByteArray(char *hexstring, char* bytearray)
{
	uint8_t str_len = strlen(hexstring);
	int i ;
    for (i = 0; i < (str_len / 2); i++) {
        sscanf(hexstring + 2*i, "%02X", &bytearray[i]);
    }
}

int ByteArrayToHexString(uint8_t *byte_array, int byte_array_len, char *hexstr, int hexstr_len)
{
    int off = 0;
    int i;
	//sprintf((char *)hexstr, "%lx", &byte_array[0]);

    for (i = 0; i < byte_array_len; i++) {
        off += snprintf(hexstr + off, hexstr_len - off,
                           "%02X", byte_array[i]);

    }

    hexstr[off] = '\0';
    LOGI("tls header profile white list start index:%s", hexstr);
    return off;
}


/*--- AT command handler ---*/

atci_status_t atci_cmd_hdlr_g3(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t resonse;
  char *param = NULL;
  uint8_t tx_buffer[260] = {0,};
  uint8_t rx_buffer[260] = {0,};
  uint16_t rx_buffer_size = sizeof(rx_buffer);

  uint32_t size = 0;
  uint16_t ret;

  LOGI("atci_cmd_hdlr_g3");
  os_memset(&resonse, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) 
  {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);
      param = strtok(parse_cmd->string_ptr, "=");
      param = strtok(NULL, "\r\n");
      LOGI("AT CMD param:%s", param);
      /*if(param == NULL){
      LOGI("not command\r\n");
      strcpy((char *)resonse.response_buf, "There is no command\n");
      resonse.response_len = strlen((char *)resonse.response_buf);
      resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      return ATCI_STATUS_ERROR;
      }*/	
      size = set_buffer_from_hexstr(tx_buffer,param);
      ret = G3_Cmd_BUFFER(tx_buffer,size,rx_buffer,&rx_buffer_size);
      if(ret != 0x0000)
      {
        resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
      }
      else
      {
        //LOG_HEXDUMP_I(ATCMD_G3,"packet : ",rx_buffer, rx_buffer_size); 
        for(int i=0;i<rx_buffer_size;i++) 
        {
          sprintf((char *)&resonse.response_buf[i*2], "%02X", rx_buffer[i]);
        }
        //resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
        resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_QUOTED_WITH_LF_CR;
      }

      resonse.response_len = rx_buffer_size*2;	
      atci_send_response(&resonse);

      param = NULL;
      break;

    case ATCI_CMD_MODE_TESTING: // rec: AT+G3=?
    case ATCI_CMD_MODE_READ:    // rec: AT+G3?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+G3
    default: 
    {
      strcpy((char *)resonse.response_buf, "Not Support\n");
      resonse.response_len = strlen((char *)resonse.response_buf);
      resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&resonse);
      break;            
    }
    break;
  }

  return ATCI_STATUS_OK;
}

/*--- AT command handler ---*/

atci_status_t atci_cmd_hdlr_g3_profile(atci_parse_cmd_param_t *parse_cmd)
{
  atci_response_t resonse;
  char *param = NULL;
  uint8_t tx_buffer[260] = {0,};
  uint8_t rx_buffer[260] = {0,};
  uint16_t rx_buffer_size = sizeof(rx_buffer);
  uint8_t operation = 0;		//0 is get, 1 is set

  uint32_t size = 0;
  uint16_t ret;

  LOGI("atci_cmd_hdlr_g3_profile");
  os_memset(&resonse, 0, sizeof(atci_response_t));

  switch (parse_cmd->mode) 
  {
    case ATCI_CMD_MODE_EXECUTION:
      LOGI("AT Executing...\r\n");
      LOGI("AT CMD received:%s ", parse_cmd->string_ptr);

      param = strtok((char *)parse_cmd->string_ptr, "=");
      param = strtok(NULL, ",");
      LOGI("AT CMD received operation mode:%s", param);
      operation = (uint8_t)atoi(param);

      if(operation == 0)
      {       //set tls header profile      
        uint8_t defCount[32]= {0,};
        uint8_t whiteListLoc[32]= {0,};
        uint8_t whiteListStIndex[32]= {0,};
        char profDesc[64] = {0,};;
        char s_defCount[32]= {0,};
        char d_defCount[32]= {0,};

        //uint8_t defCount_;
        LOGI("set tls header profile\r\n");
        param = strtok(NULL, ",");
        //eli_crlf(param,profDesc, strlen(param));
        strcpy(profDesc, param);
        LOGI("tls profile description:%s", profDesc);		

        param = strtok(NULL, ",");
        LOGI("tls profile white list definition count:%s", param);
        HexStringToByteArray(param, defCount);
        LOG_HEXDUMP_I(ATCMD_G3,"defCount : ",defCount, 32);

        param = strtok(NULL, ",");
        LOGI("tls profile white list location:%s", param);
        HexStringToByteArray(param, whiteListLoc);

        LOG_HEXDUMP_I(ATCMD_G3,"white list location : ",whiteListLoc, 32);

        param = strtok(NULL, "\r\n");
        LOGI("tls profile white list start index:%s", param);
        HexStringToByteArray(param, whiteListStIndex);

        LOG_HEXDUMP_I(ATCMD_G3,"white list start index : ",whiteListStIndex, 32);
        ret = set_tls_header_profile(/*"Can get the detail information through any profile saved in G3"*/profDesc, defCount, whiteListLoc, whiteListStIndex);

        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, "");
        }
      }
      else if(operation == 1)
      {   //get tls header profile
        char o_profDesc[64]='\0';
        uint8_t o_defCount[32]= {0,};
        uint8_t o_whiteListLoc[32]= {0,};
        uint8_t o_whiteListStIndex[32] = {0,};
        uint8_t *s_result;

        char *profDesc = (char*) pvPortMalloc(64 + 1); 
        char* s_defCount = (char*) pvPortMalloc(64 + 1);
        char* s_whiteListLoc= (char*) pvPortMalloc(64 + 1);
        char* s_whiteListStIndex= (char*) pvPortMalloc(64 + 1);
        int size;
        //char *s_result;
        const char *seperator=",";
        LOGI("get tls header profile\r\n");
        ret = get_tls_header_profile(o_profDesc, o_defCount, o_whiteListLoc,o_whiteListStIndex);
        strcpy(profDesc, o_profDesc);

        ByteArrayToHexString(o_defCount, 32, s_defCount, 64);
        //LOGI("tls header profile definition count:%s", &s_defCount[0]);

        ByteArrayToHexString(o_whiteListLoc, 32, s_whiteListLoc, 64);
        //LOGI("tls header profile white list location:%s", &s_whiteListLoc[0]);

        ByteArrayToHexString(o_whiteListStIndex, 32, s_whiteListStIndex, 64);
        //LOGI("tls header profile white list start index:%s", &s_whiteListStIndex[0]);

        s_result = (char*) pvPortMalloc(256);
        *s_result = '\0';

        strncat(s_result , profDesc ,strlen(profDesc)); 
        strcat(s_result , seperator); 
        strncat(s_result , s_defCount , 2); 
        strcat(s_result , seperator);
        strncat(s_result , s_whiteListLoc , 2); 
        strcat(s_result , seperator);
        strncat(s_result , s_whiteListStIndex , 2);

        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, s_result);
          LOGI("tls header profile information:%s", &s_result[0]);
        }
        resonse.response_len = strlen((char *)resonse.response_buf);	
        atci_send_response(&resonse);
        param = NULL;

        vPortFree(profDesc);
        profDesc = NULL;
        vPortFree(s_result);
        s_result = NULL;
        vPortFree(s_defCount);
        s_defCount = NULL;
        vPortFree(s_whiteListLoc);
        s_whiteListLoc = NULL;
        vPortFree(s_whiteListStIndex);
        s_whiteListStIndex = NULL;
        break;
      }
      else if(operation == 2)
      {   //set tls profile
        //description,key usage, key state, key type, private information,certificate information 
        //char profDesc[21] = {0,};;
        char profDesc[20] = {0,};;
        uint8_t* keysectnum = (uint8_t*) pvPortMalloc(1+1);
        uint8_t* keyusage = (uint8_t*) pvPortMalloc(1+1); 
        uint8_t* keystate = (uint8_t*) pvPortMalloc(1+1);
        uint8_t* keytype = (uint8_t*) pvPortMalloc(1+1);
        uint8_t* priInfo = (uint8_t*) pvPortMalloc(4+1);
        uint8_t* certInfo = (uint8_t*) pvPortMalloc(4+1);
		uint8_t* prov_flag = (uint8_t*) pvPortMalloc(1+1);

        LOGI("set tls profile\r\n");
        param = strtok(NULL, ",");
        strcpy(profDesc, param);
        LOGI("description:%s", profDesc);	

        param = strtok(NULL, ",");
        LOGI("key usage:%s", param);
        HexStringToByteArray(param, keysectnum);
        LOG_HEXDUMP_I(ATCMD_G3,"keyusage : ",keysectnum, 1);

        param = strtok(NULL, ",");
        LOGI("key usage:%s", param);
        HexStringToByteArray(param, keyusage);
        LOG_HEXDUMP_I(ATCMD_G3,"keyusage : ",keyusage, 1);

        param = strtok(NULL, ",");
        LOGI("key state:%s", param);
        HexStringToByteArray(param, keystate);
        LOG_HEXDUMP_I(ATCMD_G3,"white list location : ",keystate, 1);

        param = strtok(NULL, ",");
        LOGI("key type:%s", param);
        HexStringToByteArray(param, keytype);
        LOG_HEXDUMP_I(ATCMD_G3,"keyusage : ",keytype, 2);

        param = strtok(NULL, ",");
        LOGI("private info.:%s", param);
        HexStringToByteArray(param, priInfo);
        LOG_HEXDUMP_I(ATCMD_G3,"private info : ",priInfo, 4);

        param = strtok(NULL, ",");
        LOGI("cert info:%s", param);
        HexStringToByteArray(param, certInfo);
        LOG_HEXDUMP_I(ATCMD_G3,"certi info : ",certInfo, 4);

        param = strtok(NULL, "\r\n");
        LOGI("prov flag:%s", param);
        HexStringToByteArray(param, prov_flag);
        LOG_HEXDUMP_I(ATCMD_G3,"prov flag : ",prov_flag, 1);

        ret = set_tls_profile(0, *keysectnum, NULL,0,keyusage, keystate,keytype, profDesc, priInfo, certInfo, prov_flag);

        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, "");
        }
        resonse.response_len = strlen((char *)resonse.response_buf);	
        atci_send_response(&resonse);

        param = NULL;

        vPortFree(keysectnum);
        keysectnum = NULL;
        vPortFree(keyusage);
        keyusage = NULL;
        vPortFree(keystate);
        keystate = NULL;
        vPortFree(keytype);
        keytype = NULL;
        vPortFree(priInfo);
        priInfo = NULL;
        vPortFree(certInfo);
        certInfo = NULL;
        vPortFree(prov_flag);
        prov_flag = NULL;
		break;
      }
      else if(operation == 3)
      {   //get tls profile
        uint8_t* keysectnum = (uint8_t*) pvPortMalloc(1+1);
        uint8_t*  b_keyinformation = (uint8_t*) pvPortMalloc(32 + 2); 
        uint8_t  profDesc[21] = '\0';
        char* keyusage = (uint8_t*) pvPortMalloc(4); 
        char* keystate = (uint8_t*) pvPortMalloc(4);
        char* keytype = (uint8_t*) pvPortMalloc(4);
        char* priInfo = (uint8_t*) pvPortMalloc(10);
        char* certInfo = (uint8_t*) pvPortMalloc(10);
        char* s_profDesc = (char*) pvPortMalloc(42+1); 
        char* s_result = (char*) pvPortMalloc(256);
        const char *seperator=",";
        LOGI("get tls profile\r\n");
        *s_result = '\0';
        param = strtok(NULL, ",");
        LOGI("key usage:%s", param);
        HexStringToByteArray(param, keysectnum);
        LOG_HEXDUMP_I(ATCMD_G3,"keyusage : ",keysectnum, 1);

        ret = get_tls_profile(0, *keysectnum, b_keyinformation,sizeof(b_keyinformation));
        os_memcpy(profDesc, b_keyinformation + 3, 21);//description
        byteArray2String(profDesc, s_profDesc);

        ByteArrayToHexString(&b_keyinformation[0], 1, keyusage, 4);

        ByteArrayToHexString(&b_keyinformation[1], 1, keystate, 4);

        ByteArrayToHexString(&b_keyinformation[2], 1, keytype, 4);

        ByteArrayToHexString(&b_keyinformation[24], 4, priInfo, 10);

        ByteArrayToHexString(&b_keyinformation[28], 4, certInfo, 10);

        strncat(s_result , keyusage ,2); 
        strcat(s_result , seperator); 
        strncat(s_result , keystate , 2); 
        strcat(s_result , seperator);
        strncat(s_result , keytype , 2); 
        strcat(s_result , seperator);
        strncat(s_result , s_profDesc , 42); 
        strcat(s_result , seperator);
        strncat(s_result , priInfo , 8); 
        strcat(s_result , seperator);
        strncat(s_result , certInfo , 8); 
        LOGI("key information:%s", s_result);
        
        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, s_result);
        }
        resonse.response_len = strlen((char *)resonse.response_buf);	
        atci_send_response(&resonse);

        param = NULL;
        vPortFree(keysectnum);
        keysectnum = NULL;
        vPortFree(b_keyinformation);
        b_keyinformation = NULL;

        vPortFree(s_profDesc);
        s_profDesc = NULL;
        vPortFree(keyusage);
        keyusage = NULL;
        vPortFree(keystate);
        keystate = NULL;
        vPortFree(keytype);
        keytype = NULL;
        vPortFree(priInfo);
        priInfo = NULL;
        vPortFree(certInfo);
        certInfo = NULL;
        vPortFree(s_result);
        s_result = NULL;

        break;
      }
      else if(operation == 4)
      {   //set tls whitelist
        uint8_t*  CN = (uint8_t*) pvPortMalloc(256);
        int size;
        uint8_t* startWhitelistIndex = (uint8_t*) pvPortMalloc(2);
        uint8_t* indexsize = (uint8_t*) pvPortMalloc(2);
        LOGI("set tls whitelist\r\n");

        param = strtok(NULL, ",");
        LOGI("white list start index:%s", param);
        HexStringToByteArray(param, startWhitelistIndex);
        LOG_HEXDUMP_I(ATCMD_G3,"startWhitelistIndex : ",startWhitelistIndex, 1);

        param = strtok(NULL, ",");
        LOGI("key state:%s", param);
        HexStringToByteArray(param, indexsize);

        param = strtok(NULL, "\r\n");
        size = os_strlen(param);//string2ByteArray(param, CN);
        ret = set_tls_whitelist(*startWhitelistIndex, *indexsize, NULL, 0,param, size-1, 1);
        //ret = set_tls_whitelist(100, 10, NULL, 0 , CN, size, 1);

        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, "");
        }
        resonse.response_len = strlen((char *)resonse.response_buf);	
        atci_send_response(&resonse);

        param = NULL;

        vPortFree(CN);
        CN = NULL;
        vPortFree(startWhitelistIndex);
        startWhitelistIndex = NULL;
        vPortFree(indexsize);
        indexsize = NULL;
        break;
      }
      else if(operation == 5)
      {   //get tls whitelist
        uint8_t* index = (uint8_t*) pvPortMalloc(2);
        uint8_t* indexsize = (uint8_t*) pvPortMalloc(2);
        uint8_t* whiteList =  (uint8_t*) pvPortMalloc(32 + 1);//'\0';
        char* s_whitelist = (char*) pvPortMalloc(64 + 1);

        LOGI("get tls whitelist\r\n");
        param = strtok(NULL, "\r\n");
        LOGI("white list start index:%s", param);
        HexStringToByteArray(param, index);
        LOG_HEXDUMP_I(ATCMD_G3,"startWhitelistIndex : ",index, 1);

        ret = get_tls_whitelist2(*index, whiteList, sizeof(whiteList));
        byteArray2String(whiteList, s_whitelist);

        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, s_whitelist);
        }
        resonse.response_len = strlen((char *)resonse.response_buf);	
        atci_send_response(&resonse);

        param = NULL;

        vPortFree(index);
        index = NULL;
        vPortFree(indexsize);
        indexsize = NULL;
        vPortFree(s_whitelist);
        s_whitelist = NULL;
        vPortFree(whiteList);
        whiteList = NULL;
        break;
      }
      else if(operation == 9)
      {   //get tls whitelist
        ret = init_tls_whitelist(START_INDEX_WHITELIST, WHITELIST_MAX_SIZE);

        if(ret != 0)
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;
          strcpy((char *)resonse.response_buf, "");
        }
        else
        {
          resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_OK;
          strcpy((char *)resonse.response_buf, "");
        }
        resonse.response_len = strlen((char *)resonse.response_buf);	
        atci_send_response(&resonse);

        param = NULL;
        break;
      }
      resonse.response_len = strlen((char *)resonse.response_buf);	
      atci_send_response(&resonse);

      param = NULL;
      break;
    case ATCI_CMD_MODE_TESTING: // rec: AT+G3=?
    case ATCI_CMD_MODE_READ:    // rec: AT+G3?
    case ATCI_CMD_MODE_ACTIVE:  // rec: AT+G3
    default: 
    {
      strcpy((char *)resonse.response_buf, "Not Support\n");
      resonse.response_len = strlen((char *)resonse.response_buf);
      resonse.response_flag = 0 | ATCI_RESPONSE_FLAG_APPEND_ERROR;

      atci_send_response(&resonse);
      break;            
    }
    break;
  }

  return ATCI_STATUS_OK;
}

#endif /* ATCI_ICTK_COMMAND_ENABLE */
