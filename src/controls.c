#include "controls.h"
#include <pspctrl.h>
#include <stdbool.h>
#include "log.h"

struct Controls controls;

static SceCtrlData pad;
static SceCtrlData pad_prev;

void controls_init() {
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    //controls.exit = PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_UP | PSP_CTRL_TRIANGLE;
    controls.exit = PSP_CTRL_START | PSP_CTRL_CROSS;
    controls.menu_confirm = PSP_CTRL_CROSS;
    controls.menu_cancel = PSP_CTRL_CIRCLE;
    controls.menu_left = PSP_CTRL_LEFT;
    controls.menu_right = PSP_CTRL_RIGHT;
    log_debug("controls: initialised");
}

bool controls_combo_is_idle(int combo) {
    return ((pad.Buttons & combo) == combo) &&
           ((pad_prev.Buttons & combo) != combo);
}

bool controls_combo_is_pressed(int combo) {
    return ((pad.Buttons & combo) == combo) &&
           ((pad_prev.Buttons & combo) != combo);
}

bool controls_combo_is_held(int combo) {
    return ((pad.Buttons & combo) == combo) &&
           ((pad_prev.Buttons & combo) != combo);
}

bool controls_combo_is_released(int combo) {
    return ((pad.Buttons & combo) == combo) &&
           ((pad_prev.Buttons & combo) != combo);
}

int controls_get_next_inputs() {
    // record last poll (for determining state transitions)
    pad_prev = pad;
    return sceCtrlReadBufferPositive(&pad, 1);
}
