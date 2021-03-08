CELT codec prebuilt module usage guide

Brief:          This module contains the third party library for the CELT codec.

Usage:          GCC:  For the CELT codec prebuilt module, make sure to include the following:
                      1) Add the following for libs and source file:
                         LIBS += $(SOURCE_DIR)/prebuilt/middleware/third_party/audio/celt_codec/lib/libcelt.a
                CFLAGS += -I$(SOURCE_DIR)/prebuilt/middleware/third_party/audio/celt_codec/inc

Dependency:     None

Notice:         None

Relative doc:   None

Example project:None