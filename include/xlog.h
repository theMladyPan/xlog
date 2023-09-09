#ifndef __LOG_HPP
#define __LOG_HPP

#include <string>
#include <iostream>
#include <sstream>
#if defined(RP2040)
#include "pico/time.h"
#elif defined(ARDUINO)
#include "Arduino.h"
#elif defined(CONFIG_IDF_TARGET_ESP32)
#include "esp_timer.h"
#else
#include <chrono>
#endif
#include "stdio.h"
#include <cstdlib>
#include <cstring>

// log level is set in CMakeLists.txt
// #define _LOG_LEVEL 1 = ERROR
// #define _LOG_LEVEL 2 = WARNING
// #define _LOG_LEVEL 3 = INFO
// #define _LOG_LEVEL 4 = DEBUG

// macro to strip file path from __FILE__
#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // __FILENAME__

#define _CLR_BOLD "\033[1m"
#define _CLR_B_RED "\033[1;31m"
#define _CLR_B_YLW "\033[1;33m"
#define _CLR_B_GREY "\033[1;2m"
#define _CLR_RED "\033[31m"
#define _CLR_YLW "\033[33m"
#define _CLR_GREY "\033[2m"
#define _CLR_RST "\033[0m"

#ifdef NDEBUG
// do not log in release mode
#define xlog(level, msg) do { } while (0)
#else
// define xerxes_log(level, msg) to printf as a macro in format
// [Time][Log level] — [File]:[Line] [Function] — [Text]
// e.g. [0.000000][INFO] — [main.cpp:123 main] — Hello World!
#if defined(RP2040)
#define xlog(level, msg) do { \
    float timestamp = time_us_64() / 1000000.0f; \
    std::cout << _CLR_GREY << "[" << timestamp << "][" << _CLR_RST << level << _CLR_GREY << "] — [" << __FILENAME__ << ":" << __LINE__ << " " << __func__ << "()] — " << _CLR_RST << msg << std::endl; \
} while (0)
#elif defined(ARDUINO)
#define xlog(level, msg) do { \
    float timestamp = micros() / 1000000.0f; \
    std::cout << _CLR_GREY << "[" << timestamp << "][" << _CLR_RST << level << _CLR_GREY << "] — [" << __FILENAME__ << ":" << __LINE__ << " " << __func__ << "()] — " << _CLR_RST << msg << std::endl; \
} while (0)
#elif defined(CONFIG_IDF_TARGET_ESP32)
    auto now = std::chrono::steady_clock::now();
    float timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    std::cout << _CLR_GREY << "[" << timestamp << "][" << _CLR_RST << level << _CLR_GREY << "] — [" << __FILENAME__ << ":" << __LINE__ << " " << __func__ << "()] — " << _CLR_RST << msg << std::endl; \
} while (0)
#else
#define xlog(level, msg) do { \
    float timestamp = esp_timer_get_time() / 1000000.0f; \
    std::cout << _CLR_GREY << "[" << timestamp << "][" << _CLR_RST << level << _CLR_GREY << "] — [" << __FILENAME__ << ":" << __LINE__ << " " << __func__ << "()] — " << _CLR_RST << msg << std::endl; \
} while (0)
#endif // board selection
#endif // NDEBUG


// always log errors
#define xlog_error(msg) do { \
    xlog(_CLR_B_RED << "ERR " << _CLR_RST, _CLR_RED << msg << _CLR_RST); \
} while (0)

// convenience macros
#define xlog_err(msg) xlog_error(msg)
#define xloge(msg) xlog_error(msg)

// log warnings if log level is warning or higher
#if (_LOG_LEVEL >= 2)
#define xlog_warning(msg) do { \
    xlog(_CLR_B_YLW << "WARN" << _CLR_RST, _CLR_YLW << msg << _CLR_RST); \
} while (0)
#else
#define xlog_warning(msg) do { } while (0)
#endif // _LOG_LEVEL

// convenience macros
#define xlog_warn(msg) xlog_warning(msg)
#define xlogw(msg) xlog_warning(msg)


#if (_LOG_LEVEL >= 3)
#define xlog_info(msg) do { \
    xlog(_CLR_BOLD << "INFO" << _CLR_RST, msg); \
} while (0)
#else
#define xlog_info(msg) do { } while (0)
#endif // _LOG_LEVEL

// convenience macros
#define xlogi(msg) xlog_info(msg)

// log debug messages if log level is debug
#if (_LOG_LEVEL >= 4)
#define xlog_debug(msg) do { \
    xlog(_CLR_B_GREY << "DBG " << _CLR_RST, _CLR_GREY << msg << _CLR_RST); \
} while (0)
#else
#define xlog_debug(msg) do { } while (0)
#endif // _LOG_LEVEL

// convenience macros
#define xlogd(msg) xlog_debug(msg)
#define xlog_dbg(msg) xlog_debug(msg)


#endif    /* LOG_HPP */