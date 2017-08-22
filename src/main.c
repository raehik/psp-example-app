#include <pspkernel.h>

#include <stdbool.h>
#include <unistd.h>

#include "common/callback.h"
#include "log.h"
#include "controls.h"
#include "debug-screen.h"

#define MAJOR_VER 1
#define MINOR_VER 0

PSP_MODULE_INFO("hello-raehik", PSP_MODULE_USER, MAJOR_VER, MINOR_VER);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();

#define SCR_WIDTH 480
#define SCR_HEIGHT 272

// convenient RGB -> decimal colour macro
#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

/// Various initialising/deinitialising {{{
bool initialise() {
    setupExitCallback();
    initControls();
    if (!initLogging()) { return false; }
    setupDebugScreen();

    char dir_name[100];
    dir_name[99] = '\0';
    getcwd(dir_name, 99);
    log_debug("Hi!");
    log_debug(dir_name);
    return true;
}

void deinitialise() {
    sceKernelExitGame();
}
/// }}}

int main() {
    if (!initialise()) { deinitialise(); return -1; }

    bool running = isRunning();
    while (running) {
        running = mainEventLoopDebugScreen();
        if (running) { running = isRunning(); } // TODO: does this cause slowdown?
    }

    deinitialise();
    return 0;
}
