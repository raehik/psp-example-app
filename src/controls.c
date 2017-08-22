#include "controls.h"
#include <pspctrl.h>
#include <stdbool.h>

struct Controls controls;

static SceCtrlData pad;
static SceCtrlData pad_prev;

void initControls() {
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    controls.exit = PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_UP | PSP_CTRL_TRIANGLE;
    controls.menu_confirm = PSP_CTRL_CROSS;
    controls.menu_cancel = PSP_CTRL_CIRCLE;
    controls.menu_left = PSP_CTRL_LEFT;
    controls.menu_right = PSP_CTRL_RIGHT;
}

bool isPressed(int combination) {
    return ((pad.Buttons & combination) == combination) &&
           ((pad_prev.Buttons & combination) != combination);
}

int getNextInputs() {
    // record previous request (for use in determining presses/holds/releases)
    pad_prev = pad;
    return sceCtrlReadBufferPositive(&pad, 1);
}
