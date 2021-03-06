/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
* Application specific definitions.
*
* These definitions should be adjusted for your particular hardware and
* application requirements.
*
* THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
* FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
* http://www.freertos.org/a00110.html
*
* The bottom of this file contains some constants specific to running the UDP
* stack in this demo.  Constants specific to FreeRTOS+TCP itself (rather than
* the demo) are contained in FreeRTOSIPConfig.h.
*----------------------------------------------------------*/

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
#include <stdint.h>
#include <stdio.h>
#include "os_port_callback.h"
#include "os_trace_callback.h"

extern uint32_t SystemCoreClock;
#endif

#define configUSE_QUEUE_SETS		    1
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configCPU_CLOCK_HZ              ( SystemCoreClock )
#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            ( 20 )
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 610 )
#if defined(MTK_WIFI_TGN_VERIFY_ENABLE)
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 100 * 1024 ) ) /* 2 iperf instances need 68KB to run on AP mode */
#else
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 200 * 1024 ) ) /* 2 iperf instances need 68KB to run on AP mode */
#endif

#define configMAX_TASK_NAME_LEN                    ( 15 )
#define configUSE_TRACE_FACILITY                   1
#define configUSE_16_BIT_TICKS                     0
#define configIDLE_SHOULD_YIELD                    1
#define configUSE_MUTEXES                          1
#define configUSE_RECURSIVE_MUTEXES                1
#define configQUEUE_REGISTRY_SIZE                  8
#define configUSE_APPLICATION_TASK_TAG             0
#define configUSE_COUNTING_SEMAPHORES              1
#define configUSE_ALTERNATIVE_API                  0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    3      /* FreeRTOS+FAT requires 2 pointers if a CWD is supported. */
#define configRECORD_STACK_HIGH_ADDRESS            1
#define configSUPPORT_STATIC_ALLOCATION            1
//#define configUSE_TICKLESS_IDLE                    2
#define configTICKLESS_DYNAMIC_ENABLE              1
#define configENABLE_BACKWARD_COMPATIBILITY        1

//#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_STATS_FORMATTING_FUNCTIONS 1

#if defined(MTK_OS_CPU_UTILIZATION_ENABLE)
/* Run time stats gathering definitions. */
void vConfigureTimerForRunTimeStats(void);
uint32_t ulGetRunTimeCounterValue(void);
#define configGENERATE_RUN_TIME_STATS   1
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()
#define portGET_RUN_TIME_COUNTER_VALUE() ulGetRunTimeCounterValue()
#endif

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES       0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS                1
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH        10
#define configTIMER_TASK_STACK_DEPTH    ( configMINIMAL_STACK_SIZE * 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskCleanUpResources           1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTimerGetTimerTaskHandle        0
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_xQueueGetMutexHolder            1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xEventGroupSetBitsFromISR       1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_xTaskAbortDelay                 1
#define INCLUDE_pcTaskGetTaskName               1


/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
#define configPRIO_BITS             __NVIC_PRIO_BITS
#else
#define configPRIO_BITS             3      /* 32 priority levels */
#endif


/* Map the logging task's printf to the board specific output function. */


#define configPRINT_STRING( X )                     test_print( X )
//#define configPRINT_STRING( X )                     printf( "%s", X )
#define configPRINTF( X )                           printf  X


/* Sets the length of the buffers into which logging messages are written - so
 * also defines the maximum length of each log message. */
#define configLOGGING_MAX_MESSAGE_LENGTH            255

/* Set to 1 to prepend each log message with a message number, the task name,
 * and a time stamp. */
#define configLOGGING_INCLUDE_TIME_AND_TASK_NAME    1


/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			0xf  //old is 0xf ,modified by zhanguo

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    0x4

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY         (( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS)) & 0xFF )

/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#if configUSE_TICKLESS_IDLE == 1
#define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime ) vPortSuppressTicksAndSleep( xExpectedIdleTime )
#elif configUSE_TICKLESS_IDLE == 2
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
extern void tickless_handler( uint32_t xExpectedIdleTime );
#endif /*#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)*/
#define portSUPPRESS_TICKS_AND_SLEEP( xExpectedIdleTime ) tickless_handler( xExpectedIdleTime )
#endif

#if (configUSE_TICKLESS_IDLE >= 1)
#if (configCHECK_FOR_STACK_OVERFLOW > 0)
/* restore dwt stack overflow check after deep sleep */
#undef configPOST_SLEEP_PROCESSING
#define configPOST_SLEEP_PROCESSING(x)                              \
{                                                                    \
    extern void hal_dwt_init(void);                                  \
    extern void vPortCurrentTaskStackOverflowCheck(void);            \
    hal_dwt_init();                                                  \
    vPortCurrentTaskStackOverflowCheck();                            \
}
#endif /* (configCHECK_FOR_STACK_OVERFLOW > 0) */
#endif /* (configUSE_TICKLESS_IDLE >= 1) */


#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
/* for FreeRTOS trace support */
#ifdef ENABLE_RTOS_TRACE
#include "trace.h"
#endif

#include "assert.h"

extern void abort(void);
extern void platform_assert(const char *, const char *, int);

#define configASSERT( x ) if( (x) == 0 ) { platform_assert(#x, __FILE__, __LINE__); }

#include "syslog.h"
#endif /*#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)*/

/* The address of an echo server that will be used by the two demo echo client
 * tasks:
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/TCP_Echo_Clients.html,
 * http://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/UDP_Echo_Clients.html. */
#define configECHO_SERVER_ADDR0              192
#define configECHO_SERVER_ADDR1              168
#define configECHO_SERVER_ADDR2              0
#define configECHO_SERVER_ADDR3              105
#define configTCP_ECHO_CLIENT_PORT           45000

/* Default MAC address configuration.  The demo creates a virtual network
 * connection that uses this MAC address by accessing the raw Ethernet/WiFi data
 * to and from a real network connection on the host PC.  See the
 * configNETWORK_INTERFACE_TO_USE definition above for information on how to
 * configure the real network connection to use. */
#define configMAC_ADDR0                      0x88
#define configMAC_ADDR1                      0x36
#define configMAC_ADDR2                      0x6C
#define configMAC_ADDR3                      0xF2
#define configMAC_ADDR4                      0x9B
#define configMAC_ADDR5                      0xCB

/* Default IP address configuration.  Used in ipconfigUSE_DHCP is set to 0, or
 * ipconfigUSE_DHCP is set to 1 but a DNS server cannot be contacted. */
#define configIP_ADDR0                       192
#define configIP_ADDR1                       168
#define configIP_ADDR2                       0
#define configIP_ADDR3                       15

/* Default gateway IP address configuration.  Used in ipconfigUSE_DHCP is set to
 * 0, or ipconfigUSE_DHCP is set to 1 but a DNS server cannot be contacted. */
#define configGATEWAY_ADDR0                  192
#define configGATEWAY_ADDR1                  168
#define configGATEWAY_ADDR2                  0
#define configGATEWAY_ADDR3                  1

/* Default DNS server configuration.  OpenDNS addresses are 208.67.222.222 and
 * 208.67.220.220.  Used in ipconfigUSE_DHCP is set to 0, or ipconfigUSE_DHCP is
 * set to 1 but a DNS server cannot be contacted.*/
#define configDNS_SERVER_ADDR0               8
#define configDNS_SERVER_ADDR1               8
#define configDNS_SERVER_ADDR2               8
#define configDNS_SERVER_ADDR3               8

/* Default netmask configuration.  Used in ipconfigUSE_DHCP is set to 0, or
 * ipconfigUSE_DHCP is set to 1 but a DNS server cannot be contacted. */
#define configNET_MASK0                      255
#define configNET_MASK1                      255
#define configNET_MASK2                      255
#define configNET_MASK3                      0

/* The UDP port to which print messages are sent. */
#define configPRINT_PORT                     ( 15000 )

#define configPROFILING                      ( 0 )

#define configPLATFORM_NAME    "Trust-LE"

#endif /* FREERTOS_CONFIG_H */

