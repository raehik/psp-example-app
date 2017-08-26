#pragma once

#include <stdbool.h>

/**
 * Controls module.
 *
 * An individual digital button has two *states*, idle and held. The default
 * state is idle. There are four state transitions for these states, all of
 * which are valid and commonly used in control processing (state transition
 * name in brackets): idle->idle (idle), idle->held (pressed), held->held
 * (held), and held->idle (released).
 *
 * To determine state transitions, we retain the previous controller poll as
 * well as the current one.
 */

struct Controls {
    int menu_left;
    int menu_right;
    int menu_confirm;
    int menu_cancel;
    int exit;
};

void controls_init();

/**
 * Check if a combo is currently idle (idle -> idle).
 *
 * @return true if idle, else false
 */
bool controls_combo_is_idle(int combo);

/**
 * Check if a combo has just been pressed (idle -> held).
 *
 * @return true if pressed, else false
 */
bool controls_combo_is_pressed(int combo);

/**
 * Check if a combo is currently being held, and has not just been pressed (held
 * -> held).
 *
 * @return true if held and not pressed, else false
 */
bool controls_combo_is_held(int combo);

/**
 * Check if a combo has just been released (held -> idle).
 *
 * @return true if held and not pressed, else false
 */
bool controls_combo_is_released(int combo);
int controls_get_next_inputs();

struct Controls controls;
