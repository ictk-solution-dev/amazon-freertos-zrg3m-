/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
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


#ifndef __BT_MESH_MODEL_FOTA_OPCODES_H__
#define __BT_MESH_MODEL_FOTA_OPCODES_H__

/**
 *   @addtogroup BluetoothMesh Mesh
 *   @{
 *   @addtogroup BluetoothMeshFota FOTA
 *   @{
 *    bt_mesh_model_fota_opcodes.h defines the SIG Mesh Lighting Model operation codes.
*/

/**
 * @defgroup Bluetooth_mesh_fota_enum Enum
 * @{
*/


/*!
    @name Firmware update messages
    @{
*/
#define BT_MESH_ACCESS_MSG_FIRMWARE_INFORMATION_GET 0xB601
#define BT_MESH_ACCESS_MSG_FIRMWARE_INFORMATION_STATUS 0xB602
#define BT_MESH_ACCESS_MSG_FIRMWARE_UPDATE_GET 0xB603
#define BT_MESH_ACCESS_MSG_FIRMWARE_UPDATE_PREPARE 0xB604
#define BT_MESH_ACCESS_MSG_FIRMWARE_UPDATE_START 0xB605
#define BT_MESH_ACCESS_MSG_FIRMWARE_UPDATE_ABORT 0xB606
#define BT_MESH_ACCESS_MSG_FIRMWARE_UPDATE_APPLY 0xB607
#define BT_MESH_ACCESS_MSG_FIRMWARE_UPDATE_STATUS 0xB608
#define BT_MESH_ACCESS_MSG_FIRMWARE_DISTRIBUTION_GET 0xB609
#define BT_MESH_ACCESS_MSG_FIRMWARE_DISTRIBUTION_START 0xB60A
#define BT_MESH_ACCESS_MSG_FIRMWARE_DISTRIBUTION_STOP 0xB60B
#define BT_MESH_ACCESS_MSG_FIRMWARE_DISTRIBUTION_STATUS 0xB60C
#define BT_MESH_ACCESS_MSG_FIRMWARE_DISTRIBUTION_DETAIL_GET 0xB60D
#define BT_MESH_ACCESS_MSG_FIRMWARE_DISTRIBUTION_DETAIL_LIST 0xB60E
/*!  @} */

/*!
    @name Object transfer messages
    @{
*/
#define BT_MESH_ACCESS_MSG_OBJECT_TRANSFER_GET 0xB701
#define BT_MESH_ACCESS_MSG_OBJECT_TRANSFER_START 0xB702
#define BT_MESH_ACCESS_MSG_OBJECT_TRANSFER_ABORT 0xB703
#define BT_MESH_ACCESS_MSG_OBJECT_TRANSFER_STATUS 0xB704
#define BT_MESH_ACCESS_MSG_OBJECT_BLOCK_TRANSFER_START 0xB705
#define BT_MESH_ACCESS_MSG_OBJECT_BLOCK_TRANSFER_STATUS 0xB706
#define BT_MESH_ACCESS_MSG_OBJECT_CHUNK_TRANSFER_EX 0xB707
#define BT_MESH_ACCESS_MSG_OBJECT_BLOCK_GET_EX 0xB708
#define BT_MESH_ACCESS_MSG_OBJECT_CHUNK_TRANSFER 0x7D
#define BT_MESH_ACCESS_MSG_OBJECT_BLOCK_GET 0x7E
#define BT_MESH_ACCESS_MSG_OBJECT_BLOCK_STATUS 0xB709
#define BT_MESH_ACCESS_MSG_OBJECT_INFORMATION_GET 0xB70A
#define BT_MESH_ACCESS_MSG_OBJECT_INFORMATION_STATUS 0xB70B
/*! @} */

/*!
@}
@}
@}
*/

#endif // __BT_MESH_MODEL_FOTA_OPCODES_H__

