#ifndef ANIMATION_MODULE_H
#define ANIMATION_MODULE_H

#include "Arduino.h"
#include "../utility/animations.h"
#include "../utility/utility.h"
#include "../utility/queue.h"

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
uint8_t fullblock[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff};

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

Animation* currentAnimation = NULL;
uint64_t* lastUpdate;
uint8_t loopedCount = 0;

AnimationQueueNode** animationQueue;
bool showingError = false;

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

bool is_animating() {
    return currentAnimation != NULL;
}

bool should_update(uint64_t elapsedTime) {
    return is_animating() && 
        (currentAnimation->animationContext->updatedCount == 0 || elapsedTime > currentAnimation->animation->speed);
}

void get_next_animation() {
    loopedCount = 0;
    currentAnimation = dequeue(animationQueue);
}

void setup_animations() {
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, LCD_COLS, LCD_ROWS);
  }
  lcd.init();
  lcd.backlight();

  lastUpdate = (uint64_t*)malloc(sizeof(uint64_t));
  animationQueue = (AnimationQueueNode**)malloc(sizeof(AnimationQueueNode*));
  *animationQueue = NULL;

  lcd.createChar(BELL, bell);
  lcd.createChar(NOTE, note);
  lcd.createChar(CLOCK, clock);
  lcd.createChar(HEART, heart);
  lcd.createChar(DUCK, duck);
  lcd.createChar(CHECK, fullblock);
  lcd.createChar(CROSS, cross);
  lcd.createChar(RETARROW, retarrow);
  lcd.createChar(FULLBLOCK, fullblock);
}

void queue_animation(Animation* animation) {
    if (animation == NULL)
        return;

    lcd.clear();
    *lastUpdate = get_total_elapsed_milliseconds();

    if (currentAnimation == NULL) {
        currentAnimation = animation;
    } else {
        enqueue(animationQueue, animation);
    }
}

void show_error(const String message, bool canContinue) {
    if (canContinue) {
        showingError = true;
    } else {
        currentAnimation = NULL;
    }

    *lastUpdate = get_total_elapsed_milliseconds();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error: ");
    lcd.setCursor(0, 1);
    lcd.print(message);
}

void update_animations() {
    uint64_t totalTime = get_total_elapsed_milliseconds();
    uint64_t elapsedTime = totalTime - *lastUpdate;

    if (showingError && elapsedTime > SECONDS_TO_MS(ERROR_WAIT_SECONDS)) {
        showingError = false;
        lcd.clear();
    } else if (should_update(elapsedTime)) {
        AnimationDefinition* currentAnimationDef = currentAnimation->animation;
        AnimationContext* currentAnimationCtx = currentAnimation->animationContext;

        uint8_t updateCount = currentAnimationDef->updateAnimation(lcd, currentAnimationCtx);

        if (updateCount > currentAnimationCtx->updatedCount) {
            *lastUpdate = totalTime;
        } else if (updateCount == 0 && loopedCount < currentAnimationDef->loopCount) {
            *lastUpdate = totalTime;
            loopedCount++;
        } else if (updateCount == 0) {
            get_next_animation();
            return;
        }

        currentAnimationCtx->updatedCount = updateCount;
    }
}
#endif