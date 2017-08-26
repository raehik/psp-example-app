#include <pspkernel.h>
#include <stdbool.h>
#include "callback.h"

// TODO: why those values? initPriority and stackSize respectively
#define INIT_PRIORITY 0x11
#define STACK_SIZE 0xFA0

static bool exit_request = false;

bool is_running() {
    return !exit_request;
}

// Run when the user exits the game using the screen that shows up upon pressing
// the Home/PS button.
int exit_callback(int arg1, int arg2, void *common) {
    exit_request = true;
    return 0;
}

int callback_thread(SceSize args, void *argp) {
    int callbackID;

    callbackID = sceKernelCreateCallback("exit_callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(callbackID);

    sceKernelSleepThreadCB();

    return 0;
}

int callback_init() {
    SceUID threadID = sceKernelCreateThread("callback_update_thread", callback_thread, INIT_PRIORITY, STACK_SIZE, 0, NULL);
    if (threadID >= 0) {
        sceKernelStartThread(threadID, 0, NULL);
    }
    return threadID;
}
