ifeq ($(MTK_WIFI_WPS_ENABLE),y)
MINISUPP_LIB = libminisupp_wps.a
else ifeq ($(MTK_WIFI_WPA3_SAE_ENABLE),y)
MINISUPP_LIB = libminisupp_wpa3.a
else
MINISUPP_LIB = libminisupp.a
endif

LIBS    += $(SOURCE_DIR)/prebuilt/middleware/MTK/minisupp/lib/$(MINISUPP_LIB)

CFLAGS += -I$(SOURCE_DIR)/prebuilt/middleware/MTK/minisupp/inc/
