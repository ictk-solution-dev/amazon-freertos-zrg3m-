# Copyright Statement:                                                                                               
#                                                                                                                    
# (C) 2017  Airoha Technology Corp. All rights reserved.                                                             
#                                                                                                                    
# This software/firmware and related documentation ("Airoha Software") are                                           
# protected under relevant copyright laws. The information contained herein                                          
# is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.                        
# Without the prior written permission of Airoha and/or its licensors,                                               
# any reproduction, modification, use or disclosure of Airoha Software,                                              
# and information contained herein, in whole or in part, shall be strictly prohibited.                               
# You may only use, reproduce, modify, or distribute (as applicable) Airoha Software                                 
# if you have agreed to and been bound by the applicable license agreement with                                      
# Airoha ("License Agreement") and been granted explicit permission to do so within                                  
# the License Agreement ("Permitted User").  If you are not a Permitted User,                                        
# please cease any access or use of Airoha Software immediately.                                                     
# BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES                                        
# THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES                                               
# ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL                          
# WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF                             
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.                                              
# NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE                                            
# SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR                                              
# SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH                                            
# THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES                               
# THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES                       
# CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA                                  
# SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR                                   
# STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND                               
# CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,                                   
# AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,                                                 
# OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO                                          
# AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.                                                                          
#                                                                                                                    

###################################################
# Sources
KERNEL_SYSLOG_SERVICE_SRC    = kernel/service/syslog/src

ifneq ($(MTK_SYSLOG_VERSION_2), y)
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/syslog_cli.c
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/syslog.c
endif
ifeq ($(MTK_SYSLOG_VERSION_2), y)
CFLAGS += -DMTK_SYSLOG_VERSION_2
ifeq ($(MTK_SYSLOG_SUB_FEATURE_STRING_LOG_SUPPORT), y)
CFLAGS += -DMTK_SYSLOG_SUB_FEATURE_STRING_LOG_SUPPORT
endif
ifeq ($(MTK_SYSLOG_SUB_FEATURE_BINARY_LOG_SUPPORT), y)
CFLAGS += -DMTK_SYSLOG_SUB_FEATURE_BINARY_LOG_SUPPORT
endif
ifeq ($(MTK_SYSLOG_SUB_FEATURE_MSGID_TO_STRING_LOG_SUPPORT), y)
CFLAGS += -DMTK_SYSLOG_SUB_FEATURE_MSGID_TO_STRING_LOG_SUPPORT
endif
ifeq ($(MTK_SYSLOG_SUB_FEATURE_USB_ACTIVE_MODE), y)
CFLAGS += -DMTK_SYSLOG_SUB_FEATURE_USB_ACTIVE_MODE
endif
ifeq ($(MTK_SYSLOG_SUB_FEATURE_OFFLINE_DUMP_ACTIVE_MODE), y)
CFLAGS += -DMTK_SYSLOG_SUB_FEATURE_OFFLINE_DUMP_ACTIVE_MODE
endif
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/syslog_version_2.c
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/portable/src/syslog_port_uart.c
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/portable/src/syslog_port_usb.c
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/portable/src/syslog_port_ram_flash.c
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/portable/src/syslog_port_bt_online.c
KERNEL_SERVICE_SYSLOG_FILES += $(KERNEL_SYSLOG_SERVICE_SRC)/portable/src/syslog_port_device.c
endif

C_FILES += $(KERNEL_SERVICE_SYSLOG_FILES)

###################################################
# include path
CFLAGS += -I$(SOURCE_DIR)/kernel/service/syslog/inc
CFLAGS += -I$(SOURCE_DIR)/kernel/service/syslog/src/portable/inc
CFLAGS += -I$(SOURCE_DIR)/kernel/service/exception_handler/inc

