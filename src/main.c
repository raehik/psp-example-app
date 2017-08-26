#include <pspkernel.h>
#include <stdbool.h>
#include "common/callback.h"
#include "log.h"
#include "controls.h"
#include "debug-screen.h"

#define MAJOR_VER 1
#define MINOR_VER 1

PSP_MODULE_INFO("PSP Example App", PSP_MODULE_USER, MAJOR_VER, MINOR_VER);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();

#define SCR_WIDTH 480
#define SCR_HEIGHT 272

// convenient RGB -> decimal colour macro
#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

/// Various initialising/deinitialising {{{
bool initialise() {
    setupExitCallback();
    controls_init();
    if (!logging_init(LOG_LEVEL_DEBUG, "ms0:/testlog.txt")) { return false; }
    debugscreen_init();

    return true;
}

void deinitialise() {
    logging_deinit();
    sceKernelExitGame();
}
/// }}}

int main() {
    if (!initialise()) { deinitialise(); return -1; }

    bool running = isRunning();
    while (running) {
        running = debugscreen_main_event_loop();
        if (running) { running = isRunning(); } // TODO: does this cause slowdown?
    }

    deinitialise();
    return 0;
}
