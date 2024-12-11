#include "Arduino.h"
#include "ui_module.h"
#include "../utility/ui_screen.h"

UIMode* modes = NULL;
uint8_t modeCount = 0;
uint8_t modeIndex = 0;
uint8_t screenIndex = 0;
uint8_t uiState = UI_STATE_IDLE;

UIScreen get_current_screen() {
    if (modes != NULL) {
        return modes[modeIndex].screens[screenIndex];
    }
}

void setup_ui(UIMode* uiModes, uint8_t uiModeCount) {
    modes = uiModes;
    modeCount = uiModeCount;
}

void check_mode_listener() {
    if (modes != NULL) {
        uint8_t retVal = modes[modeIndex].inputListener();
    }
}

void check_screen_listener() {
    if (modes != NULL) {
        uint8_t retVal = modes[modeIndex].screens[screenIndex].inputListener();
    }
}

void check_for_input() {
    // check global

    //
}

void update_ui() {
    switch (uiState)
    {
    case UI_STATE_SWITCHING_MODE:
        break;
    case UI_STATE_SWITCHING_SCREEN:
        break;
    case UI_STATE_IDLE:
    default:
        break;
    }
}