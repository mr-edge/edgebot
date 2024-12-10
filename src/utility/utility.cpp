#include "utility.h"
#include "Arduino.h"

uint64_t get_total_elapsed_milliseconds() {
    return (uint64_t)millis();
}