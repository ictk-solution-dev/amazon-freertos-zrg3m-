/** 
  *****************************************************************************
  * @file               : i2c_sw.h
  * @author             : Department 1, R&D Center, Security SoC Division
  * @version            : V1.0.0
  * @date               : 25-April-2019
  * @brief              : Header of i2c_sw.c file.
  *****************************************************************************
  * Copyright (c) 2017 ICTK Co., LTD. All rights reserved.
  */

#ifndef __I2C_SW_H
#define __I2C_SW_H

/* Includes ------------------------------------------------------------------*/
#include "g3_define.h"   
#include "i2c.h"
#include "hal_gpio.h"
#include "hal_gpio_7687.h"


/* Variables ------------------------------------------------------------------*/

/* Defines ------------------------------------------------------------------*/


#define I2C_CLOCK_HIGH_TIME     5 /// 100khz  = 10us -> 10/2 -> 5us
#define I2C_CLOCK_LOW_TIME      5 /// 100khz  = 10us -> 10/2 -> 5us

#define G3_I2C_DEVICE_ADDRESS   100 /// 100 = 0x64, 0x64<<1 = 0xC8
// I2C Default Device Address
#define G3_DEFAULT_I2C_DEVICE_ADDRESS  0xC8



///--- SCL : HAL_GPIO_27 --------------------------------------------------------
#define SCL_MODE_SET_IN         hal_gpio_set_direction(HAL_GPIO_27, 0)
#define SCL_MODE_SET_OUT        hal_gpio_set_direction(HAL_GPIO_27, 1)
#define SCL_H                   hal_gpio_set_output(HAL_GPIO_27, 1)
#define SCL_L                   hal_gpio_set_output(HAL_GPIO_27, 0)

#define SCL_READ()              halgetGPIO_DOUT(HAL_GPIO_27)
#define SCL_RESET               HAL_GPIO_DATA_LOW


///--- SDA : HAL_GPIO_28 --------------------------------------------------------
#define SDA_MODE_SET_IN         hal_gpio_set_direction(HAL_GPIO_28, 0)
#define SDA_MODE_SET_OUT        hal_gpio_set_direction(HAL_GPIO_28, 1)
#define SDA_H                   hal_gpio_set_output(HAL_GPIO_28, 1)
#define SDA_L                   hal_gpio_set_output(HAL_GPIO_28, 0)

#define SDA_READ_OUT()          halgetGPIO_DOUT(HAL_GPIO_28)
#define SDA_READ_IN()           halgetGPIO_DIN(HAL_GPIO_28)
#define SDA_RESET               HAL_GPIO_DATA_LOW



/* Exported functions --------------------------------------------------------*/   
int  _i2c_start(void);
int  _i2c_init(void);
void _i2c_stop(void);
void _i2c_ack(void);
void _i2c_noack(void);
int  _i2c_waitack(void);
int  _i2c_wakeup(uint16_t wli_delay_time, uint16_t whi_delay_time);
void _i2c_sendbyte(uint8_t sendbyte);
uint8_t _i2c_receivebyte(void);


#endif /*__I2C_SW_H*/

/************************ (c) COPYRIGHT 2017 ICTK Co., LTD. *****END OF FILE*****/
