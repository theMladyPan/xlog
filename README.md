# XLog
## Overview
A header only library for simple log output which can be completely compiled out in release mode

## Usage
```cpp
#include "xlog.h"

#undef NDEBUG
#define _LOG_LEVEL 4 // 1: error, 2: warning, 3: info, 4: debug

void setup() {
    Serial.begin(115200);
}

void loop() {
    xlog_error("This is error message");
    xlog_warning("This is warning message");
    xlog_info("This is info message");
    xlog_debug("This is debug message");

    /* This will print out nice colored output
    [0.014762][ERR]         — [main.cpp:11 loop()] — This is error message
    [0.016108][WARN]        — [main.cpp:12 loop()] — This is warning message
    [0.023394][INFO]        — [main.cpp:13 loop()] — This is info message
    [0.031463][DBG]         — [main.cpp:14 loop()] — This is debug message
    */

    #define NDEBUG
    // none of these should be printed
    xlog_error("This is error message");
    xlog_warning("This is warning message");
    xlog_info("This is info message");
    xlog_debug("This is debug message");
}
```