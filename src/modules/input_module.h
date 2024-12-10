#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include "Arduino.h"

#define BUTTON_ROWS 2
#define BUTTON_COLS 2

#define BUTTON_COUNT BUTTON_COLS * BUTTON_ROWS

#define BUTTON_INPUT_PIN_START 3

#define BUTTON_STATE_OPEN 0
#define BUTTON_STATE_PRESSED 1
#define BUTTON_STATE_HELD 2
#define BUTTON_STATE_RELEASED 3

bool check_keycombo(uint8_t flag, uint8_t button_state);

void setup_input();
void poll_input();

#endif