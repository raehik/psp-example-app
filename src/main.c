#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>

#include "common/callback.h"

#define MAJOR_VER 0
#define MINOR_VER 2

PSP_MODULE_INFO("hello-raehik", PSP_MODULE_USER, MAJOR_VER, MINOR_VER);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_MAX();

#define printf pspDebugScreenPrintf

int main() {
    pspDebugScreenInit();
    setupExitCallback();

    int running = isRunning();

    while (running) {
        running = isRunning();

        pspDebugScreenSetXY(0, 0);
        printf("Hello raehik!");
        sceDisplayWaitVblankStart();
    }

    sceKernelExitGame();
    return 0;
}
