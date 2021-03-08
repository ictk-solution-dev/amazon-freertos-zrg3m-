/* 
  *****************************************************************************
  * @file           : g3_semaphore.c
  * @author         : Department 1, R&D Center, Security SoC Division
  * @version        : V1.0.0
  * @date           : 21-June-2017
  * @brief          : Communication Layer of g3 Library
  *****************************************************************************
  * Copyright (c) 2017 ICTK Co., LTD. All rights reserved.
  */
    
#include <string.h>
#include "puf_if.h"
#include "syslog.h"
#include "g3_semaphore.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "sys.h"

#ifdef G3_SEMAPHORE

static SemaphoreHandle_t g3_mutex;

void g3_mutex_new()
{
    g3_mutex = xSemaphoreCreateMutex();
    
    if ( ( g3_mutex ) != NULL )
        xSemaphoreGive( ( g3_mutex ) ); 
}

void g3_mutex_lock()
{
   for(;;)
   {  
       if(xSemaphoreTake(g3_mutex, portMAX_DELAY)== pdTRUE)
          break;
   }
}

void g3_mutex_unlock()
{
   if ( ( g3_mutex ) != NULL )
      xSemaphoreGive( ( g3_mutex ) ); 
}

void g3_mutex_delete()
{
    if ( ( g3_mutex ) != NULL )
        vSemaphoreDelete( ( g3_mutex ) ); 
}


#endif
