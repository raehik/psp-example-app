#pragma once
#include <stdbool.h>

struct Controls {
    int menu_left;
    int menu_right;
    int menu_confirm;
    int menu_cancel;
    int exit;
};

void initControls();
bool isPressed(int combination);
int getNextInputs();

struct Controls controls;
