#pragma once

#include <stdbool.h>

void debugscreen_init();
bool debugscreen_main_event_loop();
void debugscreen_print_msg(char *msg);
