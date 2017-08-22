#pragma once

#include <stdbool.h>

typedef enum log_level {
    LOG_LEVEL_NONE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
} log_level;

#define log_debug(msg) log_msg(LOG_LEVEL_DEBUG, msg)

bool initLogging();
bool log_msg(log_level level, char *msg);
