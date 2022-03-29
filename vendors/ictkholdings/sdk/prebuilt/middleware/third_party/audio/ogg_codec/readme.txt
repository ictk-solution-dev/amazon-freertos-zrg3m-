OGG codec prebuilt module usage guide

Brief:          This module contains the third party library for the OGG codec.

Usage:          GCC:  For the OGG codec prebuilt module, make sure to include the following:
                      1) Add the following for libs and source file:
                         LIBS += $(SOURCE_DIR)/prebuilt/middleware/third_party/audio/ogg_codec/lib/libogg_celt.a
                CFLAGS += -I$(SOURCE_DIR)/prebuilt/middleware/third_party/audio/ogg_codec/inc
                CFLAGS += -DOGG_OPUS_ENABLE
                         APP_FILES      += $(APP_PATH_SRC)/opus_proc.c
                         APP_FILES      += $(APP_PATH_SRC)/oggcelt_decode.c
                         APP_FILES      += $(APP_PATH_SRC)/oggcelt_encode.c
                      2) Module.mk provides different options to enable or disable according to the profiles.
                         Please configure the related options on the specified GCC/feature.mk.
                         MTK_OGG_OPUS_ENABLE = y

Dependency:     OGG codec prebuilt module is only effective when the OGG codec module also exists.

Notice:         None

Relative doc:   None

Example project:None