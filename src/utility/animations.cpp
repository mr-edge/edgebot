#include "Arduino.h"
#include "animations.h" 
#include <LiquidCrystal_I2C.h>
#include "utility.h"

void print_offscreen(LiquidCrystal_I2C lcd, String message, int8_t colPos, uint8_t row) {
    int8_t startIndex = colPos * -1;
    uint8_t messageLength = message.length();
    
    if (colPos < 0) {
        lcd.setCursor(0, row);
        lcd.print(message.substring(startIndex));
    } else if (colPos > LCD_COLS - messageLength) {
        lcd.setCursor(colPos, row);
        uint8_t overrun = LCD_COLS - colPos;
        lcd.print(message.substring(0, overrun));

    } else {
        lcd.setCursor(colPos, row);
        lcd.print(message);
    }
}

uint8_t noop (LiquidCrystal_I2C lcd, anim_ctx_t* animation) {
    return 0;
}

uint8_t wrap_scroll_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation) {
    lcd.clear();

    for (uint8_t i = 0; i < animation->rows; i++) {
        print_offscreen(lcd, animation->rowMessage[i], LCD_COLS - animation->updatedCount, i);
    }
    
    if (animation->updatedCount > LCD_COLS + animation->longestLineLength) {
        return 0;
    }
    return animation->updatedCount + 1;
}


uint8_t scroll_rows_in_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation) {
    lcd.clear();

    if (animation->rows < 2) {
        return 0;
    }


    for (uint8_t i = 0; i < animation->rows; i++) {
        uint8_t columnBoundary = LCD_COLS * (i + 1);
        if (animation->updatedCount > columnBoundary) {
            print_offscreen(lcd, animation->rowMessage[i], 0, i);
        } else {
            uint8_t colPos = columnBoundary - animation->updatedCount;
            print_offscreen(lcd, animation->rowMessage[i], colPos, i);
            return animation->updatedCount + 1;
        }
    }

    return 0;
}


uint8_t flip_row_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation) {
    lcd.clear();

    for (uint8_t i = 0; i < animation->rows; i++) {
        uint8_t row = (i + animation->updatedCount) % animation->rows;
        print_offscreen(lcd, animation->rowMessage[row], 0, i);
    }
    
    if (animation->updatedCount > LCD_ROWS) {
        return 0;
    }
    return animation->updatedCount + 1;
}

uint8_t center_blink_animation(LiquidCrystal_I2C lcd, anim_ctx_t* animation) {
    lcd.clear();

    bool blinkOn = animation->updatedCount & 0x1 == 0;

    for (uint8_t i = 0; i < animation->rows; i++) {
        uint8_t midpoint = (LCD_COLS - animation->longestLineLength) >> 1;
        uint8_t j;
        String message = animation->rowMessage[i];
        
        if (blinkOn) {
            for (j = 0; j < midpoint; j++) {
                lcd.print("#");
            }
        }

        print_offscreen(lcd, message, midpoint, i);

        if (blinkOn) {
            for (j = midpoint + message.length(); j < LCD_COLS; j++) {
                lcd.print("#");
            }
        }
    }
    
    if (animation->updatedCount > LCD_ROWS) {
        return 0;
    }
    return animation->updatedCount + 1;
}