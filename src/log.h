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

/**
 * Initialise the logging module.
 *
 * @return false on error, else true
 */
bool logging_init(log_level level, char *out);
void logging_deinit();

/**
 * Log a message with a given level.
 *
 * @return false on error, else true
 */
bool log_msg(log_level level, char *msg);
