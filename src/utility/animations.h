#ifndef Animations_H
#define Animations_H

#include "Arduino.h"

#ifndef ARDUINO
#define ARDUINO 100
#endif

#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27
#define LCD_ROWS 2
#define LCD_COLS 16

#define MAX_QUEUED_ANIMATIONS 5

#define BELL 1
#define NOTE 2
#define CLOCK 3
#define HEART 4
#define DUCK 5
#define CHECK 6
#define CROSS 7
#define RETARROW 8
#define FULLBLOCK 9

#define ERROR_WAIT_SECONDS 4

typedef struct AnimationContext {
    String* rowMessage;
    uint8_t rows;
    uint8_t longestLineLength;
    uint8_t updatedCount;
} anim_ctx_t;

typedef struct AnimationDefinition {
    uint16_t speed;
    uint8_t loopCount;
    uint8_t (*updateAnimation)(LiquidCrystal_I2C lcd, anim_ctx_t* animation);
} anim_def_t;

struct Animation {
    struct AnimationDefinition* animation;
    anim_ctx_t* animationContext;
};

uint8_t noop(LiquidCrystal_I2C lcd, anim_ctx_t* animation);
uint8_t wrap_scroll_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation);
uint8_t flip_row_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation);
uint8_t scroll_rows_in_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation);
uint8_t center_blink_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation);

#endif