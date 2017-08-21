#include <pspkernel.h>
#include <stdbool.h>
#include "callback.h"

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
    int threadID = 0;

    // TODO: why those values? initPriority and stackSize respectively
    threadID = sceKernelCreateThread("callback_update_thread", callbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, NULL);

    if (threadID >= 0) {
        sceKernelStartThread(threadID, 0, NULL);
    }

    return threadID;
}
