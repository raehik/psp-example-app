#include "debug-screen.h"
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "controls.h"
#include "screen.h"
#include "log.h"

#define PATH_MAX MAXPATHLEN
#define DEBUG_COLS 68
#define DEBUG_ROWS 34

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

void debugscreen_init() {
    pspDebugScreenInit();
    pspDebugScreenClearLineDisable();
    srand(time(NULL));
    log_debug("debug screen: initialised");
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

void debugscreen_print_msg(char *msg) {
    pspDebugScreenPrintf(msg);
}

Screen curScreen = SCREEN_MAIN;

void setScreen(Screen newScreen) {
    pspDebugScreenClear();
    curScreen = newScreen;
}

bool debugscreen_main_event_loop() {
    controls_get_next_inputs();
    if (curScreen == SCREEN_MAIN) {
        if (controls_combo_is_pressed(controls.exit)) { setScreen(SCREEN_EXIT_CONFIRM); return true; }
        sceDisplayWaitVblankStart();
        pspDebugScreenSetXY(0, 0);
        printAllCellIdentifiers(DEBUG_COLS, DEBUG_ROWS);
    } else if (curScreen == SCREEN_EXIT_CONFIRM) {
        if (controls_combo_is_pressed(controls.menu_cancel)) { setScreen(SCREEN_MAIN); return true; }
        if (controls_combo_is_pressed(controls.menu_confirm)) { setScreen(SCREEN_EXIT); return true; }
        sceDisplayWaitVblankStart();
        pspDebugScreenSetXY(0, 0);
        printCellIdentifiersWithEmptyMiddle(DEBUG_COLS, DEBUG_ROWS, 1, 16);
        pspDebugScreenSetXY((DEBUG_COLS/2)-16+1, DEBUG_ROWS/2);
        pspDebugScreenPrintf("Exit? (X = confirm, O = cancel)");
    } else if (curScreen == SCREEN_EXIT) {
        sceDisplayWaitVblankStart();
        pspDebugScreenClear();
        pspDebugScreenSetXY(0, 0);
        pspDebugScreenPrintf("Exiting...\n");
        sceKernelDelayThread(1000000);

        char dir_name[PATH_MAX];
        char s[100];
        itoa(PATH_MAX, s);
        getcwd(dir_name, PATH_MAX);
        pspDebugScreenPrintf("CWD: %s\n", dir_name);
        pspDebugScreenPrintf("PATH_MAX: %s\n", s);
        sceKernelDelayThread(1000000);

        return false;
    }
    return true;
}
