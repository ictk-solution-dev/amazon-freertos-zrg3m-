/*
 * FreeRTOS V1.1.4
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Test includes */
#include "aws_test_runner.h"

/* AWS library includes. */
#include "iot_system_init.h"
#include "iot_logging_task.h"
#include "iot_wifi.h"
#include "aws_clientcredential.h"
#include "aws_dev_mode_key_provisioning.h"
#include "bt_hal_manager_types.h"

/* Logging Task Defines. */
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 15 )
#define mainLOGGING_TASK_STACK_SIZE         ( configMINIMAL_STACK_SIZE * 8 )

/* Unit test defines. */
#define mainTEST_RUNNER_TASK_STACK_SIZE     ( configMINIMAL_STACK_SIZE * 16 )

/* MediaTek */
#include "sys_init.h"
#include "atci_main.h"
#include "nvdm.h"
#include "hal_pinmux_define.h"
#include "bsp_gpio_ept_config.h"
#ifdef HAL_GPIO_LOW_POWER_ENABLED
#include "hal_lp.h"
#endif

/* Ictk */
#include "g3_nvdm_config.h"
#include "g3_tls_setup.h"
#define WIFI_FW_DEBUG_LOG_PORT

/* Set the following to 1 to enable debugging. */
#define MTK_DEBUGGER  0

/**
 * @brief Application task startup hook for applications using Wi-Fi. If you are not
 * using Wi-Fi, then start network dependent applications in the vApplicationIPNetorkEventHook
 * function. If you are not using Wi-Fi, this hook can be disabled by setting
 * configUSE_DAEMON_TASK_STARTUP_HOOK to 0.
 */
void vApplicationDaemonTaskStartupHook( void );

#if( configUSE_DAEMON_TASK_STARTUP_HOOK != 1 )
	/**
	 * @brief Wrapper for vApplicationDaemonTaskStartupHook.
	 */
	static void vApplicationWrapperTask( void * pvParameters );
#endif

#ifdef MTK_MINICLI_ENABLE
	/**
	 * @brief CLI task startup function.
	 */
	void vCliTaskStartup( void );
#endif

/**
 * @brief Connects to WiFi.
 */
static void prvWifiConnect( void );

/**
 * @brief Initializes the board.
 */
static void prvMiscInitialization( void );

/*-----------------------------------------------------------*/

#ifdef ICTK_TLS
g3_cfg_t g3_config = {0};
#endif
#if defined(MBEDTLS_SSL_CIPHERSUITES_RSA)    
extern uint32_t cipher_suite_flag;
#endif    


/**
 * @brief Application runtime entry point.
 */
int main( void )
{
    #if ( MTK_DEBUGGER != 0 )
        { volatile int wait_ice = 1 ; while ( wait_ice ) ; }
    #endif

    /* Perform any hardware initialization that does not require the RTOS to be
     * running.  */
    prvMiscInitialization();

    /* console print can be used after console UART ports have been configured
     * in prvMiscInitialization(). */
    //configPRINT_STRING( "hello world\n" );

#if ( configUSE_DAEMON_TASK_STARTUP_HOOK != 1 )
    configASSERT( xTaskCreate( vApplicationWrapperTask,
                               "wrap",
                               configTIMER_TASK_STACK_DEPTH,
                               NULL,
                               tskIDLE_PRIORITY + 1,
                               NULL ) == pdPASS );
#endif

    /* Create tasks that are not dependent on the WiFi being initialized. */
    xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
                            tskIDLE_PRIORITY + 2,
                            mainLOGGING_MESSAGE_QUEUE_LENGTH );

    /* Start the scheduler.  Initialization that requires the OS to be running,
     * including the WiFi initialization, is performed in the RTOS daemon task
     * startup hook. */
    vTaskStartScheduler();

    return 0;
}
/*-----------------------------------------------------------*/


#ifndef MTK_DEBUG_LEVEL_NONE
log_create_module(main, PRINT_LEVEL_ERROR);

LOG_CONTROL_BLOCK_DECLARE(main);
LOG_CONTROL_BLOCK_DECLARE(common);
LOG_CONTROL_BLOCK_DECLARE(hal);
LOG_CONTROL_BLOCK_DECLARE(lwip);
LOG_CONTROL_BLOCK_DECLARE(minisupp);
LOG_CONTROL_BLOCK_DECLARE(inband);
LOG_CONTROL_BLOCK_DECLARE(wifi);

log_control_block_t *syslog_control_blocks[] = {
    &LOG_CONTROL_BLOCK_SYMBOL(main),
    &LOG_CONTROL_BLOCK_SYMBOL(common),
    &LOG_CONTROL_BLOCK_SYMBOL(hal),
    &LOG_CONTROL_BLOCK_SYMBOL(lwip),
    &LOG_CONTROL_BLOCK_SYMBOL(minisupp),
    &LOG_CONTROL_BLOCK_SYMBOL(inband),
    &LOG_CONTROL_BLOCK_SYMBOL(wifi),
    NULL
};

static void syslog_config_save(const syslog_config_t *config)
{
    char *syslog_filter_buf;

    syslog_filter_buf = (char*)pvPortMalloc(SYSLOG_FILTER_LEN);
    configASSERT(syslog_filter_buf != NULL);
    syslog_convert_filter_val2str((const log_control_block_t **)config->filters, syslog_filter_buf);
    vPortFree(syslog_filter_buf);
}

static uint32_t syslog_config_load(syslog_config_t *config)
{
    uint32_t sz = SYSLOG_FILTER_LEN;
    char *syslog_filter_buf;

    syslog_filter_buf = (char*)pvPortMalloc(SYSLOG_FILTER_LEN);
    configASSERT(syslog_filter_buf != NULL);
    syslog_convert_filter_str2val(config->filters, syslog_filter_buf);
    vPortFree(syslog_filter_buf);

    return 0;
}
#endif

static void prvMiscInitialization( void )
{
    /* Do system initialization, eg: hardware, nvdm, logging and random seed. */
    system_init();
    
#ifdef MTK_NVDM_ENABLE
    /* nvdm init */
    nvdm_init();
    user_check_default_value();
#endif
    
#ifndef MTK_DEBUG_LEVEL_NONE
    log_init(syslog_config_save, syslog_config_load, syslog_control_blocks);
#endif
    
#ifdef MTK_AT_PRINT
    hal_pinmux_set_function(HAL_GPIO_2, HAL_GPIO_2_UART1_RX_CM4);
    hal_pinmux_set_function(HAL_GPIO_3, HAL_GPIO_3_UART1_TX_CM4); 
    atci_init(HAL_UART_1);
#endif    
           
    /* init GPIO settings generated by easy pinmux tool (ept). */
    bsp_ept_gpio_setting_init();

#ifdef HAL_GPIO_LOW_POWER_ENABLED
    hal_lp_set_gpio_sleep_mode();
#endif
    
#ifdef ICTK_TLS
    if (0 != g3_config_init(&g3_config))                           
    {
      LOG_E(common, "g3 config init fail");
      return;
    }
    
    g3_cert_init();
#ifdef G3_PKCS11    
    G3_pkcs11_init();
#endif
#endif    
    
#ifdef WIFI_FW_DEBUG_LOG_PORT
    volatile unsigned int    reg;

    reg  = *( ( volatile unsigned int * )0x81023030 );
    reg &= 0xFFFF0FFF;
    *( ( volatile unsigned int * )( 0x81023030 ) ) = reg;

    reg  = *( ( volatile unsigned int * )0x80025110 );
    reg &= 0xFFFF0FFF;
    *( ( volatile unsigned int * )0x80025110 ) = reg;
#endif
}
/*-----------------------------------------------------------*/

#if( configUSE_DAEMON_TASK_STARTUP_HOOK != 1 )
    static void vApplicationWrapperTask( void * pvParameters )
    {
	#ifdef MTK_MINICLI_ENABLE
	    vCliTaskStartup();
	#endif

        vApplicationDaemonTaskStartupHook();

        vTaskDelete( NULL );
    }
#endif
/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook( void )
{
    /* FIX ME: Perform any hardware initialization, that require the RTOS to be
     * running, here. */
    //vDevModeKeyProvisioning();

    /* FIX ME: If your MCU is using Wi-Fi, delete surrounding compiler directives to
     * enable the unit tests and after MQTT, Bufferpool, and Secure Sockets libraries
     * have been imported into the project. If you are not using Wi-Fi, see the
     * vApplicationIPNetworkEventHook function. */
    if( SYSTEM_Init() == pdPASS )
    {
        /* Connect to the wifi before running real jobs. */
        prvWifiConnect();

        /* Create the task to run unit tests. */
        xTaskCreate( TEST_RUNNER_RunTests_task,
                     "RunTests_task",
                     mainTEST_RUNNER_TASK_STACK_SIZE,
                     NULL,
                     tskIDLE_PRIORITY,
                     NULL );
    }
}
/*-----------------------------------------------------------*/

void prvWifiConnect( void )
{
    WIFINetworkParams_t xJoinAPParams;
    WIFIReturnCode_t xWifiStatus;

    xWifiStatus = WIFI_On();

    if( xWifiStatus == eWiFiSuccess )
    {
        configPRINTF( ( "WiFi module initialized. Connecting to AP...\r\n" ) );
    }
    else
    {
        configPRINTF( ( "WiFi module failed to initialize.\r\n" ) );

        while( 1 )
        {
        }
    }

    /* Setup parameters. */
    xJoinAPParams.ucSSIDLength     = strlen( clientcredentialWIFI_SSID );
    memcpy(&xJoinAPParams.ucSSID[0], clientcredentialWIFI_SSID, xJoinAPParams.ucSSIDLength);
    xJoinAPParams.xPassword.xWPA.ucLength = strlen( clientcredentialWIFI_PASSWORD );
    memcpy(&xJoinAPParams.xPassword.xWPA.cPassphrase[0], clientcredentialWIFI_PASSWORD, xJoinAPParams.xPassword.xWPA.ucLength);
    xJoinAPParams.xSecurity        = clientcredentialWIFI_SECURITY;

    xWifiStatus = WIFI_ConnectAP( &( xJoinAPParams ) );

    if( xWifiStatus == eWiFiSuccess )
    {
        configPRINTF( ( "WiFi Connected to AP. Creating tasks which use network...\r\n" ) );
    }
    else
    {
        configPRINTF( ( "WiFi failed to connect to AP.\r\n" ) );

        while( 1 )
        {
            taskYIELD();
        }
    }
}
/*-----------------------------------------------------------*/

BTStatus_t bleStackInit( void )
{
    return eBTStatusSuccess;
}

/*-----------------------------------------------------------*/
/**
 * @brief User defined Idle task function.
 *
 * @note Do not make any blocking operations in this function.
 */
void vApplicationIdleHook( void )
{
    static TickType_t xLastPrint = 0;
    TickType_t xTimeNow;
    const TickType_t xPrintFrequency = pdMS_TO_TICKS( 5000 );

    xTimeNow = xTaskGetTickCount();

    if( ( xTimeNow - xLastPrint ) > xPrintFrequency )
    {
        configPRINTF( ( "." ) );
        xLastPrint = xTimeNow;
    }
}
