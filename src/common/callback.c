#include <pspkernel.h>
#include <stdbool.h>
#include "callback.h"

// TODO: why those values? initPriority and stackSize respectively
#define INIT_PRIORITY 0x11
#define STACK_SIZE 0xFA0

static bool exitRequest = false;

bool isRunning() {
    return !exitRequest;
}

// Run when the user exits the game using the screen that shows up upon pressing
// the Home/PS button.
int exitCallback(int arg1, int arg2, void *common) {
    exitRequest = true;
    return 0;
}

int callbackThread(SceSize args, void *argp) {
    int callbackID;

    callbackID = sceKernelCreateCallback("exit_callback", exitCallback, NULL);
    sceKernelRegisterExitCallback(callbackID);

    sceKernelSleepThreadCB();

    return 0;
}

int setupExitCallback() {
    SceUID threadID = sceKernelCreateThread("callback_update_thread", callbackThread, INIT_PRIORITY, STACK_SIZE, 0, NULL);
    if (threadID >= 0) {
        sceKernelStartThread(threadID, 0, NULL);
    }
    return threadID;
}
