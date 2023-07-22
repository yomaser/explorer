#pragma once

#include <stdint.h>

enum GAIN_AMP_RATE {
    GAIN_AMP_1X = 0b000,
    GAIN_AMP_2X = 0b001,
    GAIN_AMP_4X = 0b010,
    GAIN_AMP_8X = 0b011,
    GAIN_AMP_16X = 0b100,
    GAIN_AMP_32X = 0b101,
    GAIN_AMP_64X = 0b110,
};
