#include "debug-screen.h"
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <time.h>
#include <stdlib.h>

#include "controls.h"
#include "screen.h"

#define DEBUG_COLS 68
#define DEBUG_ROWS 34

void setupDebugScreen() {
    pspDebugScreenInit();
    pspDebugScreenClearLineDisable();
    srand(time(NULL));
}

void printAllCellIdentifiers(int cols, int rows) {
    char cell_identifier[2];
    cell_identifier[1] = '\0';

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == 0)|(i == rows-1)|(j == 0)|(j == cols-1)) {
                cell_identifier[0] = '.';
            } else {
                cell_identifier[0] = (rand() % 26) + 65;
            }
            pspDebugScreenPrintf(cell_identifier);
        }
    }
}

void printCellIdentifiersWithEmptyMiddle(int cols, int rows, int space_height, int space_width) {
    char cell_identifier[2];
    cell_identifier[1] = '\0';

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((i == 0)|(i == rows-1)|(j == 0)|(j == cols-1)) {
                cell_identifier[0] = '.';
            } else if (((rows/2) - space_height <= i && i <= (rows/2) + space_height) &&
                       ((cols/2) - space_width - 1 < j && j < (cols/2) + space_width + 1)) {
                // FIXME: will break if the "empty middle" is the entire screen
                // because we don't set the Y if it rolls over to the next line
                pspDebugScreenSetXY(pspDebugScreenGetX()+1, pspDebugScreenGetY());
                continue;
            } else {
                cell_identifier[0] = (rand() % 26) + 65;
            }
            pspDebugScreenPrintf(cell_identifier);
        }
    }
}

void debug_screen_print_msg(char *msg) {
    pspDebugScreenPrintf(msg);
}

Screen curScreen = SCREEN_MAIN;

void setScreen(Screen newScreen) {
        pspDebugScreenClear();
            curScreen = newScreen;
}

bool mainEventLoopDebugScreen() {
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
        printCellIdentifiersWithEmptyMiddle(DEBUG_COLS, DEBUG_ROWS, 1, 16);
        pspDebugScreenSetXY((DEBUG_COLS/2)-16+1, DEBUG_ROWS/2);
        pspDebugScreenPrintf("Exit? (X = confirm, O = cancel)");
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
