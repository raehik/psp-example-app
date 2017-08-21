#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common/callback.h"
#include "controls.h"
#include "screen.h"

#define MAJOR_VER 1
#define MINOR_VER 0

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
    initControls();
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
            if (i == 0)           { char_as_str[0] = '.'; }
            else if (i == rows-1) { char_as_str[0] = '.'; }
            if (j == 0)           { char_as_str[0] = '.'; }
            else if (j == cols-1) { char_as_str[0] = '.'; }
            pspDebugScreenPrintf(char_as_str);
        }
    }
}

void printCellIdentifiersWithEmptyMiddle(int cols, int rows) {
    int space_height = 3;
    int space_width = 18;

    char char_as_str[2];
    char_as_str[0] = '0';
    char_as_str[1] = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char_as_str[0] += 1;
            char_as_str[0] = (rand() % 26) + 65;
            if (i == 0) { char_as_str[0] = '.'; }
            else if (i == rows-1) { char_as_str[0] = '.'; }
            if (j == 0) { char_as_str[0] = '.'; }
            else if (j == cols-1) { char_as_str[0] = '.'; }
            if (((rows/2) - space_height <= i && i <= (rows/2) + space_height) &&
                ((cols/2) - space_width - 1 < j && j < (cols/2) + space_width + 1)) { char_as_str[0] = ' '; }
            pspDebugScreenPrintf(char_as_str);
        }
    }
}

Screen curScreen = SCREEN_MAIN;

void setScreen(Screen newScreen) {
    curScreen = newScreen;
}

bool mainEventLoop() {
    getNextInputs();
    if (curScreen == SCREEN_MAIN) {
        if (isPressed(controls.exit)) { setScreen(SCREEN_EXIT_CONFIRM); return true; }
        sceDisplayWaitVblankStart();
        pspDebugScreenSetXY(0, 0);
        printAllCellIdentifiers(DEBUG_COLS, DEBUG_ROWS);
    } else if (curScreen == SCREEN_EXIT_CONFIRM) {
        if (isPressed(controls.menu_cancel)) { setScreen(SCREEN_MAIN); return true; }
        if (isPressed(controls.menu_confirm)) { setScreen(SCREEN_EXIT); return true; }
        sceDisplayWaitVblankStart();
        pspDebugScreenSetXY(0, 0);
        printCellIdentifiersWithEmptyMiddle(DEBUG_COLS, DEBUG_ROWS);
    } else if (curScreen == SCREEN_EXIT) {
        sceDisplayWaitVblankStart();
        pspDebugScreenClear();
        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf("Exiting...");
        sceKernelDelayThread(1000000);
        return false;
    }

    return true;
}

int main() {
    initialise();

    bool running = isRunning();
    while (running) {
        running = mainEventLoop();
        if (running) { isRunning(); } // TODO: does this cause slowdown?
    }

    deinitialise();
    return 0;
}
