smtcn module usage guide

Brief:  To control some IOT devices, we allow the devices to connect to an AP, but most IOT devices
        do not have an input interface (e.g. a keypad or display) so we cannot directly input the
        password and SSID of an AP. The smart connection is a solution to this problem. This module
        is the implementation of the Airoha smart connection.
Usage:
        GCC: For smtcn, make sure to include the following with the module:
            1) Configure the following options in the GCC/feature.mk file:
               MTK_SMTCN_V4_ENABLE = ? /* MTK_SMTCN_V4_ENABLE = y or MTK_SMTCN_V4_ENABLE = n*/
               MTK_SMTCN_V5_ENABLE = ? /* MTK_SMTCN_V5_ENABLE = y or MTK_SMTCN_V5_ENABLE = n*/
            2) If you define MTK_SMTCN_V4_ENABLE = y, you must add $(SOURCE_DIR)/prebuild/middleware/MTK/smtcn/lib/libmc_smtcn_protected.a in your project
               If you define MTK_SMTCN_V5_ENABLE = y, you must add $(SOURCE_DIR)/prebuild/middleware/MTK/smtcn/lib/libbc_smtcn_protected.a in your project

        KEIL: For smtcn:
             1) You can define the MTK_SMTCN_V4_ENABLE or MTK_SMTCN_V5_ENABLE macro in your project
             2) If you define MTK_SMTCN_V4_ENABLE, you must add $(SOURCE_DIR)/prebuild/middleware/MTK/smtcn/lib/libmcsmtcn_CM4_Keil.lib in your project
                If you define MTK_SMTCN_V5_ENABLE, you must add $(SOURCE_DIR)/prebuild/middleware/MTK/smtcn/lib/libbcsmtcn_CM4_Keil.lib in your project

        IAR: For smtcn:
            1) You can define the MTK_SMTCN_V4_ENABLE or MTK_SMTCN_V5_ENABLE macro in your project
            2) If you define MTK_SMTCN_V4_ENABLE, you must add $(SOURCE_DIR)/prebuild/middleware/MTK/smtcn/lib/libmcsmtcn_CM4_IAR.lib in your project
               If you define MTK_SMTCN_V5_ENABLE, you must add $(SOURCE_DIR)/prebuild/middleware/MTK/smtcn/lib/libbcsmtcn_CM4_IAR.lib in your project

Dependency:     None

Notice:         None

Relative doc:   Please refer to the Wi-Fi API reference and Wi-Fi Dev Guide under the doc folder for more detail.

Example project: Please refer to any project which calls smart_config_test_cli() by wifi cli: "smart connect"  or "smart stop".
