#include "input_module.h"
#include "Arduino.h"

uint64_t lastPolled = 0;
uint8_t lastPolledInputFlag;
uint8_t currentPolledInputFlag;

bool check_keycombo(uint8_t flag, uint8_t button_state) {
    for (uint8_t i = 0x1000; i < BUTTON_COUNT; i >>= 1) {
        if (flag & i) {
            switch (button_state)
            {
            case BUTTON_STATE_OPEN:
                if (currentPolledInputFlag & i != 0)
                    return false;
                break;
            case BUTTON_STATE_PRESSED:
                if (currentPolledInputFlag & i != 1)
                    return false;
                break;
            case BUTTON_STATE_HELD:
                if (currentPolledInputFlag & i != 1 || lastPolledInputFlag & i != currentPolledInputFlag & i)
                    return false;
                break;
            case BUTTON_STATE_RELEASED:
                if (currentPolledInputFlag & i != 0 || lastPolledInputFlag & i != 1)
                    return false;
                break;
            default:
                return false;         
            }
        }
    }
    return true;
}

// void update_last_polled_input() {
//     for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
//         lastPolledInputFlag[i] = currentPolledInputFlag[i];
//     }
// }

void setup_input() {
    lastPolledInputFlag = 0;
    currentPolledInputFlag = 0;
}

uint8_t get_current_input_state() {
    uint8_t input = 0;
    for (uint8_t i = 0; i < BUTTON_ROWS; i++) {
        for (uint8_t j = 0; j < BUTTON_COLS; j++) {
            if (digitalRead(BUTTON_INPUT_PIN_START + (j + (i * BUTTON_ROWS))) == LOW) {
                input |= 1;
            }
            input >>= 1;
        }
    }

    return input;
}

void poll_input() {
    lastPolledInputFlag = currentPolledInputFlag;
    currentPolledInputFlag = get_current_input_state();
}