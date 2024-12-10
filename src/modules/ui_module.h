#ifndef UI_MODULE_H
#define UI_MODULE_H

#include "Arduino.h"
#include "../utility/ui_screen.h"

#define UI_STATE_IDLE 0
#define UI_STATE_SWITCHING_SCREEN 1
#define UI_STATE_SWITCHING_MODE 2
#define UI_STATE_ACTIVE 3

UIScreen get_current_screen();

void setup_ui(UIMode* modes, uint8_t modeCount);
void update_ui();
#endif