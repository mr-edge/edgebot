#ifndef EDGEBOTUTILITY_H
#define EDGEBOTUTILITY_H

#include "Arduino.h"

#define MS_TO_SECONDS(m) m << 10
#define SECONDS_TO_MS(s) s >> 10

uint64_t get_total_elapsed_milliseconds();

#endif