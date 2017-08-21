#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include <time.h>
#include <stdlib.h>

#include "common/callback.h"

#define MAJOR_VER 0
#define MINOR_VER 5

PSP_MODULE_INFO("hello-raehik", PSP_MODULE_USER, MAJOR_VER, MINOR_VER);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();

#define DEBUG_COLS 68
#define DEBUG_ROWS 34
#define SCR_WIDTH 480
#define SCR_HEIGHT 272

// convenient RGB -> decimal colour macro
#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

/// Various initialising/deinitialising {{{
void setupDebugScreen() {
    pspDebugScreenInit();
    pspDebugScreenClearLineDisable();
}

void initialise() {
    setupExitCallback();
    srand(time(NULL));
    setupDebugScreen();
}

void deinitialise() {
    sceKernelExitGame();
}
/// }}}

void printAllCellIdentifiers(int cols, int rows) {
    char char_as_str[2];
    char_as_str[0] = '0';
    char_as_str[1] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char_as_str[0] += 1;
            char_as_str[0] = (rand() % 26) + 65;
            if (i == 0) { char_as_str[0] = '0'; }
            if (i == rows-1) { char_as_str[0] = '1'; }
            pspDebugScreenPrintf(char_as_str);
        }
    }
}

void mainEventLoop() {
    sceDisplayWaitVblankStart();
    pspDebugScreenSetXY(0, 0);
    printAllCellIdentifiers(DEBUG_COLS, DEBUG_ROWS);
}

int main() {
    initialise();

    int running = isRunning();
    while (running) {
        mainEventLoop();
        running = isRunning();
    }

    deinitialise();
    return 0;
}
