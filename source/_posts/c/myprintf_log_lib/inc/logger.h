#ifndef __logger_h__
#define __logger_h__

#include <stdio.h>
#include "myprintf.h"

#define test_print_func myprintf

#define MODULE_NAME  "[default]"

#define INFO 1
#define WARNING 2
#define DEBUG 3

#define LOG(DebugLevel, format, ...)   \
        do{  \
            switch (DebugLevel)  \
            {  \
            case INFO:  \
                test_print_func(MODULE_NAME" "); \
                test_print_func(format, ##__VA_ARGS__);  \
                break;  \
            case WARNING: \
                test_print_func(MODULE_NAME" "); \
                test_print_func("%s : %d : ",__FUNCTION__, __LINE__); \
                test_print_func(format, ##__VA_ARGS__);  \
                break;  \
            case DEBUG:  \
                test_print_func(MODULE_NAME" "); \
                test_print_func("%s : %s : %d : ",__FILE__, __FUNCTION__,__LINE__); \
                test_print_func(format, ##__VA_ARGS__);  \
                break; \
            default:   \
                break;  \
            }   \
        }while(0)

#define LOG_INF(...)  LOG(INFO,##__VA_ARGS__)
#define LOG_WAR(...)  LOG(WARNING,##__VA_ARGS__)
#define LOG_DBG(...)  LOG(DEBUG,##__VA_ARGS__)

#endif
