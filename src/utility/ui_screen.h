#ifndef UISCREEN_H
#define UISCREEN_H

#include "Arduino.h"

struct UIScreen {
    String title;
    int8_t (*inputListener)();
};

struct UIMode {
    String title;
    struct UIScreen* screens;
    uint8_t screenCount;
    int8_t (*inputListener)();
};
#endif