#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define MBEDTLS_CONFIG_FILE             "config-aws-iot.h"

#include <errno.h>
#include "wrap_heap.h"
#include "FreeRTOS.h"
#include MBEDTLS_CONFIG_FILE

#define MTK_AT_PRINT

#ifdef MTK_AT_PRINT
#include "test_print.h"
#endif

#define MTK_LOAD_MAC_ADDR_FROM_EFUSE
#define MTK_PING_OUT_ENABLE
#define PCFG_OS                         2
#define _REENT_SMALL
#define MTK_BSPEXT_ENABLE
#define MTK_HAL_LOWPOWER_ENABLE
#define MTK_LWIP_ENABLE
#define MTK_MINISUPP_ENABLE
#define MTK_WIFI_WPS_ENABLE
#define CONFIG_REPEATER

#define MTK_HTTPCLIENT_SSL_ENABLE
#define MTK_IPERF_ENABLE

#define PRODUCT_VERSION                 7697
#define MTK_FLASH_DIRECT_DL
#define MTK_PATCH_DL_ENABLE
#define MTK_CM4_SCAN_TABLE_ENABLE
#define MTK_WIFI_REPEATER_ENABLE
#define MTK_NVDM_ENABLE
#define MTK_EXTERNAL_FLASH_ENABLE
#define MTK_SMTCN_V5_ENABLE
#define MTK_WIFI_PMF_ENABLE
#define BT_GATTS_SERVICE_CHANGED

#define USE_HAL_DRIVER
#define DATA_PATH_87

//#define MTK_DEBUG_LEVEL_NONE
//#define MTK_CM4_WIFI_TASK_ENABLE


#define configOVERRIDE_DEFAULT_TICK_CONFIGURATION
#define CFG_SUPPORT_SMNT_PROTO                  2
#define SUPPORT_MBEDTLS
#define FREERTOS_ENABLE

#define AWS_IOT_TEST_ENABLE
#define UNITY_INCLUDE_CONFIG_H
#define AMAZON_FREERTOS_ENABLE_UNIT_TESTS
//#define MTK_HAL_PLAIN_LOG_ENABLE


//------------------------------------------------------------------------------
/*              DEBUG_LOG_CONFIG      */
//------------------------------------------------------------------------------
#define __BT_DEBUG__
#undef MTK_DEBUG_LEVEL_INFO         //need undef
//#undef MTK_DEBUG_LEVEL_WARNING
//#undef MTK_DEBUG_LEVEL_ERROR


//------------------------------------------------------------------------------
/*              G3_CONFIG      */
//------------------------------------------------------------------------------
//#define ICTK_G3_I2C_DMA
#define G3_SEMAPHORE
#define G3_PKCS11 
#define G3_MAX_CERT_SIZE                    ( 3000 )

//------------------------------------------------------------------------------
/*              ICTK_CONFIG      */
//------------------------------------------------------------------------------
#define ICTK_TLS_FOR_AWSTEST
#define ATCI_CH_TESTLOG_PRINT_FOR_AWSTEST
#define ICTK_TLS                                               
#define ICTK_TLS_PREMASTER_IN_PUF                                 
#undef ICTK_TLS_DEBUG                      
#undef MBEDTLS_PREMASTERSECRET

//------------------------------------------------------------------------------
/*              TEST_CONFIG      */
//------------------------------------------------------------------------------
#define DOXYGEN
#define MQTT_DO_NOT_USE_CUSTOM_CONFIG

#endif /* __GLOBAL_H__ */
