#pragma once

#include <stdint.h>

typedef enum {
    GAIN_RATE_1X = 0b000,
    GAIN_RATE_2X = 0b001,
    GAIN_RATE_4X = 0b010,
    GAIN_RATE_8X = 0b011,
    GAIN_RATE_16X = 0b100,
    GAIN_RATE_32X = 0b101,
    GAIN_RATE_64X = 0b110,
} GainRate;
