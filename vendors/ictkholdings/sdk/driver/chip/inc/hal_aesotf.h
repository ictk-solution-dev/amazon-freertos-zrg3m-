/* Copyright Statement:
 *
 * (C) 2019  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */

#ifndef __HAL_AESOTF_H__
#define __HAL_AESOTF_H__
#include "hal_platform.h"

#ifdef HAL_AESOTF_MODULE_ENABLED

#include "hal_define.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @defgroup hal_aesotf_define Define
  * @{
  */

/** @brief This macro defines the block size of AESOTF operation. The unit is in bytes.
  */
#define HAL_AESOTF_BLOCK_SIZES        (16)

/** @brief This macro defines the key length of AESOTF 128 bits. The unit is in bytes.
  */
#define HAL_AESOTF_KEY_LENGTH_128    (16)

/** @brief This macro defines the key length of AESOTF 192 bits. The unit is in bytes.
  */
#define HAL_AESOTF_KEY_LENGTH_192    (24)

/** @brief This macro defines the key length of AESOTF 256 bits. The unit is in bytes.
  */
#define HAL_AESOTF_KEY_LENGTH_256    (32)

/** @brief This macro defines the size of initial vector. The unit is in bytes.
  */
#define HAL_AESOTF_NONCE_LENGTH     (16)

// This macro defines the number of setting region.
#define HAL_AESOTF_REGION_0     (0)
#define HAL_AESOTF_REGION_1     (1)
#define HAL_AESOTF_REGION_2     (2)
#define HAL_AESOTF_REGION_3     (3)
#define HAL_AESOTF_REGION_4     (4)
#define HAL_AESOTF_REGION_5     (5)
#define HAL_AESOTF_REGION_6     (6)
#define HAL_AESOTF_REGION_7     (7)
#define HAL_AESOTF_REGION_ALL   (8)

// This macro defines the key source.
#define HAL_AESOTF_KEY_SOURCE_EFUSE1    (0)
#define HAL_AESOTF_KEY_SOURCE_EFUSE2    (1)
#define HAL_AESOTF_KEY_SOURCE_SWKEY     (2)
#define HAL_AESOTF_KEY_SOURCE_CKDF1     (3)
#define HAL_AESOTF_KEY_SOURCE_CKDF2     (4)
#define HAL_AESOTF_KEY_SOURCE_NUM       (5)

/**
  * @}
  */


/** @defgroup hal_aesotf_enum Enum
  * @{
  */

/** @brief This enum defines the HAL interface return value.
  */
typedef enum {
    HAL_AESOTF_STATUS_BUSY  = -100,    /**< crypto hw is busy. */
    HAL_AESOTF_STATUS_ERROR = -1,      /**< An error occurred. */
    HAL_AESOTF_STATUS_OK = 0           /**< No error occurred. */
} hal_aesotf_status_t;


/**
  * @}
  */

/** @defgroup hal_aes_struct Struct
  * @{
  */

/** @brief This structure defines the buffer used in the operation. */
typedef struct {
    uint8_t *buffer;  /**< Data buffer. */
    uint32_t length;  /**< Data length. */
} hal_aesotf_buffer_t;

/**
  * @}
  */

/**
 * @brief      This function initializes the AESOTF engine.
 * @return
 * @par    Example
 * Sample code, please refer to @ref HAL_AES_Driver_Usage_Chapter
 *
 */
hal_aesotf_status_t hal_aesotf_init(void);


/**
 * @brief     This function sets up the region for AESOTF engine.
 *
 * @param[in] begin_address is the start of region.
 * @param[in] end_address is the end of region.
 * @param[in] region can be chose from 0 to 7 (8 regions).
 * @return
 * @par    Example
 * Sample code, please refer to @ref HAL_AES_Driver_Usage_Chapter
 *
 */
hal_aesotf_status_t hal_aesotf_set_region(uint32_t begin_address, uint32_t end_address, uint8_t region);


/**
 * @brief      This function turns on the AESOTF engine.
 *
 * @param[in]  key is used to encrypt/decrypt the data.
 * @param[in]  nonce is the element of AESOTF engine.
 * @param[in]  key_src chooses the key source for AESOTF engine.
 * @return
 * @par    Example
 * Sample code, please refer to @ref HAL_AES_Driver_Usage_Chapter
 *
 */
hal_aesotf_status_t hal_aesotf_enable(hal_aesotf_buffer_t *key, uint8_t nonce[HAL_AESOTF_NONCE_LENGTH], uint8_t key_src);


/**
 * @brief  This function turns off the AESOTF engine.
 *
 * @return
 * @par    Example
 * Sample code, please refer to @ref HAL_AES_Driver_Usage_Chapter
 *
 */
hal_aesotf_status_t hal_aesotf_disable(void);

#ifdef __cplusplus
}
#endif

/**
* @}
* @}
*/
#endif /* HAL_AESOTF_MODULE_ENABLED */

#endif /* __HAL_AESOTF_H__ */

