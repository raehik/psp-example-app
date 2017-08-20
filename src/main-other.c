#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspctrl.h>

#include "common/callback.h"

#define MAJOR_VER 0
#define MINOR_VER 3

PSP_MODULE_INFO("hello-raehik", PSP_MODULE_USER, MAJOR_VER, MINOR_VER);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();

#define printf pspDebugScreenPrintf

int main() {
    pspDebugScreenInit();
    setupExitCallback();

    SceCtrlData pad;
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

    int running = isRunning();
    while (running) {
        pspDebugScreenSetXY(0, 0);
        printf("Hello raehik!\n\n");
        sceDisplayWaitVblankStart();
        printf("analog x: %d\n", pad.Lx);
        printf("analog y: %d\n\n", pad.Ly);

        sceCtrlPeekBufferPositive(&pad, 1);
        if (pad.Buttons != 0) {
            if (pad.Buttons & PSP_CTRL_START) {
                printf("hit Start - exiting...");
                running = 0;
            }
            if (pad.Buttons & PSP_CTRL_SELECT)      printf("Select");
            if (pad.Buttons & PSP_CTRL_UP)          printf("Up");
			if (pad.Buttons & PSP_CTRL_DOWN)        printf("Down");
			if (pad.Buttons & PSP_CTRL_RIGHT)       printf("Right");
			if (pad.Buttons & PSP_CTRL_LEFT)        printf("Left");
			if (pad.Buttons & PSP_CTRL_CROSS)       printf("Cross");
			if (pad.Buttons & PSP_CTRL_CIRCLE)      printf("Circle");
			if (pad.Buttons & PSP_CTRL_SQUARE)      printf("Square");
			if (pad.Buttons & PSP_CTRL_TRIANGLE)    printf("Triangle");
			if (pad.Buttons & PSP_CTRL_LTRIGGER)    printf("L-trigger");
			if (pad.Buttons & PSP_CTRL_RTRIGGER)    printf("R-trigger");
        }
        running = isRunning();
    }

    sceKernelExitGame();
    return 0;
}
