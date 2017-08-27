#include "log.h"
#include <pspiofilemgr.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static struct {
    log_level level;
    char *out;
} logger;


// TODO: replace magic number file descriptor number? (must be 0 or +ve int)
bool logging_init(log_level level, char *out) {
    logger.level = level;
    logger.out = out;

    // check that the file exists (if not, create it) and that we can open &
    // write (append) to it
    int fd = sceIoOpen(logger.out, PSP_O_WRONLY | PSP_O_APPEND | PSP_O_CREAT, 0777);
    if (fd <= -1) {
        // couldn't open file
        return false;
    } else {
        sceIoClose(fd);
    }

    log_debug("logging: initialised");
    return true;
}

void logging_deinit() {
    log_debug("logging: deinitialised");
}

// TODO: efficiency concerns:
//   * wasting memory with the fmt_now[100], use dynamic allocation/realloc (?)
//   * could save strlen(log_str), it's used twice
//   * strcat is slow
bool log_msg(log_level level, char *msg) {
    // do nothing and return true if we're configured not to log anything
    if (logger.level == LOG_LEVEL_NONE) { return true; }
    else if (logger.level <= level) {
        char fmt_now[200];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(fmt_now, sizeof(fmt_now), "%FT%T%z ", tm);

        // allocate memory: date + msg + \n
        // TODO: could probably shave off a byte b/c strcat removes 1 null char
        char *log_str = malloc(sizeof(fmt_now) + strlen(msg) + 1);
        strcpy(log_str, fmt_now);
        strcat(log_str, msg);
        strcat(log_str, "\n");

        int fd = sceIoOpen(logger.out, PSP_O_WRONLY | PSP_O_APPEND, 0777);
        sceIoWrite(fd, log_str, strlen(log_str));
        sceIoClose(fd);
        free(log_str);
    }
    return true;
}
