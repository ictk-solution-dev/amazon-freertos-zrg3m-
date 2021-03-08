#ifndef WIFI_LOG_H
#define WIFI_LOG_H

#ifndef MTK_DEBUG_LEVEL_NONE
#include "syslog.h"
#endif

extern const char *mem_err_ptr;
extern const char *addr_err_ptr;
extern const char *rxfilter_err_ptr;
extern const char *port_err_ptr;

extern void wifi_msg_output(int module, const char *func, int line, int level, const char *message, ...);
extern void wifi_hex_dump(int moudle, const char *func, int line, int level, const void *data, int length, const char *message, ...);
extern int wifi_msg_output_rom(const char *message, ...);
extern void wifi_hex_dump_rom(char *message, unsigned char *data, unsigned int length);

#ifndef MTK_DEBUG_LEVEL_NONE
#define WIFI_LOG_CONTROL_BLOCK_DECLARE  \
    LOG_CONTROL_BLOCK_DECLARE(inband);  \
    LOG_CONTROL_BLOCK_DECLARE(wifi)

#define WIFI_LOG_CONTROL_BLOCK_SYMBOL   \
    &LOG_CONTROL_BLOCK_SYMBOL(inband),  \
    &LOG_CONTROL_BLOCK_SYMBOL(wifi)
#endif

#ifdef DETAIL_LOG_ENABLE
#define FUNC_NAME       __FUNCTION__
#define LINE_INFO       __LINE__
#else
#define FUNC_NAME       ""
#define LINE_INFO       0
#endif   

#define WIFI_MODULE_ID          0

#define WIFILOG_LEVEL_DEBUG     3
#define WIFILOG_LEVEL_INFO      2
#define WIFILOG_LEVEL_WARN      1
#define WIFILOG_LEVEL_ERROR     0

#if defined(MTK_DEBUG_LEVEL_DEBUG)

#define WIFI_LOG_D(message, ...)    \
do { \
    wifi_msg_output(WIFI_MODULE_ID, \
                        FUNC_NAME, \
                        LINE_INFO, \
                        WIFILOG_LEVEL_DEBUG, \
                        (message), \
                        ##__VA_ARGS__); \
}while(0)

#define WIFI_HEXDUMP_D(message, data, len, ...) \
do { \
    wifi_hex_dump(WIFI_MODULE_ID, \
                    FUNC_NAME, \
                    LINE_INFO, \
                    WIFILOG_LEVEL_DEBUG, \
                    (data), \
                    (len), \
                    (message), \
                    ##__VA_ARGS__); \
}while(0)

#else

#define WIFI_LOG_D(message, ...)
#define WIFI_HEXDUMP_D(message, data, len, ...)

#endif


#if defined(MTK_DEBUG_LEVEL_INFO)

#define WIFI_LOG_I(message, ...)    \
do { \
    wifi_msg_output(WIFI_MODULE_ID, \
                        FUNC_NAME, \
                        LINE_INFO, \
                        WIFILOG_LEVEL_INFO, \
                        (message), \
                        ##__VA_ARGS__); \
}while(0)

#define WIFI_HEXDUMP_I(message, data, len, ...) \
do { \
    wifi_hex_dump(WIFI_MODULE_ID, \
                    FUNC_NAME, \
                    LINE_INFO, \
                    WIFILOG_LEVEL_INFO, \
                    (data), \
                    (len), \
                    (message), \
                    ##__VA_ARGS__); \
}while(0)

#else

#define WIFI_LOG_I(message, ...)
#define WIFI_HEXDUMP_I(message, data, len, ...)

#endif

#if defined(MTK_DEBUG_LEVEL_WARNING)

#define WIFI_LOG_W(message, ...)    \
do { \
    wifi_msg_output(WIFI_MODULE_ID, \
                        FUNC_NAME, \
                        LINE_INFO, \
                        WIFILOG_LEVEL_WARN, \
                        (message), \
                        ##__VA_ARGS__); \
}while(0)

#define WIFI_HEXDUMP_W(message, data, len, ...) \
do { \
    wifi_hex_dump(WIFI_MODULE_ID, \
                    FUNC_NAME, \
                    LINE_INFO, \
                    WIFILOG_LEVEL_WARN, \
                    (data), \
                    (len), \
                    (message), \
                    ##__VA_ARGS__); \
}while(0)

#else

#define WIFI_LOG_W(message, ...)
#define WIFI_HEXDUMP_W(message, data, len, ...)

#endif

#if defined(MTK_DEBUG_LEVEL_ERROR)

#define WIFI_LOG_E(message, ...)    \
do { \
    wifi_msg_output(WIFI_MODULE_ID, \
                        FUNC_NAME, \
                        LINE_INFO, \
                        WIFILOG_LEVEL_ERROR, \
                        (message), \
                        ##__VA_ARGS__); \
}while(0)

#define WIFI_HEXDUMP_E(message, data, len, ...) \
do { \
    wifi_hex_dump(WIFI_MODULE_ID, \
                    FUNC_NAME, \
                    LINE_INFO, \
                    WIFILOG_LEVEL_ERROR, \
                    (data), \
                    (len), \
                    (message), \
                    ##__VA_ARGS__); \
}while(0)

#else

#define WIFI_LOG_E(message, ...)
#define WIFI_HEXDUMP_E(message, data, len, ...)

#endif

#if defined(MTK_DEBUG_LEVEL_ERROR)

#define WIFI_MEM_ALLOC_ERROR()      wifi_msg_output(WIFI_MODULE_ID, FUNC_NAME, LINE_INFO, WIFILOG_LEVEL_ERROR, mem_err_ptr)
#define WIFI_NULL_PTR_ERROR()       wifi_msg_output(WIFI_MODULE_ID, FUNC_NAME, LINE_INFO, WIFILOG_LEVEL_ERROR, addr_err_ptr)
#define WIFI_RXFILTER_ERROR()       wifi_msg_output(WIFI_MODULE_ID, FUNC_NAME, LINE_INFO, WIFILOG_LEVEL_ERROR, rxfilter_err_ptr)
#define WIFI_PORT_ERROR()           wifi_msg_output(WIFI_MODULE_ID, FUNC_NAME, LINE_INFO, WIFILOG_LEVEL_ERROR, port_err_ptr)

#else

#define WIFI_MEM_ALLOC_ERROR()
#define WIFI_NULL_PTR_ERROR()
#define WIFI_RXFILTER_ERROR()
#define WIFI_PORT_ERROR()

#endif

#endif