#include "log.h"
#include <pspkernel.h>
#include <string.h>

static struct {
    log_level level;
    char *format;
    char *out;
} logger;

bool initLogging() {
    logger.level = LOG_LEVEL_DEBUG;
    logger.out = "ms0:/testlog.txt";
    logger.format = "test: ";

    // check that the file exists (if not, create it) and that we can open &
    // write (append) to it
    int fd = sceIoOpen(logger.out, PSP_O_WRONLY | PSP_O_APPEND | PSP_O_CREAT, 0777);
    if (fd <= -1) {
        // TODO: replace magic number?
        // couldn't open file
        return false;
    } else {
        sceIoClose(fd);
    }
    return true;
}

bool log_msg(log_level level, char *msg) {
    // do nothing and return true if we're configured not to log anything
    if (logger.level == LOG_LEVEL_NONE) { return true; }
    else if (logger.level <= level) {
        int fd = sceIoOpen(logger.out, PSP_O_WRONLY | PSP_O_APPEND, 0777);
        sceIoWrite(fd, msg, strlen(msg));
        sceIoWrite(fd, "\n", 1);
        sceIoClose(fd);
    }
    return true;
}
