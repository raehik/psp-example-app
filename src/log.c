#include "log.h"
#include <pspkernel.h>
#include <stdlib.h>
#include <string.h>

static struct {
    log_level level;
    char *prefix;
    char *out;
} logger;


// TODO: replace magic number file descriptor number? (must be 0 or +ve int)
bool initLogging(log_level level, char *out) {
    logger.level = level;
    logger.out = out;
    logger.prefix = "test: ";

    // check that the file exists (if not, create it) and that we can open &
    // write (append) to it
    int fd = sceIoOpen(logger.out, PSP_O_WRONLY | PSP_O_APPEND | PSP_O_CREAT, 0777);
    if (fd <= -1) {
        // couldn't open file
        return false;
    } else {
        sceIoClose(fd);
    }
    return true;
}

// TODO: efficiency concerns:
//   * could save strlen(log_str), it's used twice
//   * strcat is slow
bool log_msg(log_level level, char *msg) {
    // do nothing and return true if we're configured not to log anything
    if (logger.level == LOG_LEVEL_NONE) { return true; }
    else if (logger.level <= level) {
        // allocate memory: prefix, msg, \n
        char *log_str = malloc(strlen(logger.prefix) + strlen(msg) + 1);
        strcpy(log_str, logger.prefix);
        strcat(log_str, msg);
        strcat(log_str, "\n");

        int fd = sceIoOpen(logger.out, PSP_O_WRONLY | PSP_O_APPEND, 0777);
        sceIoWrite(fd, log_str, strlen(log_str));
        sceIoClose(fd);
        free(log_str);
    }
    return true;
}
