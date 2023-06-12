#pragma once

#include <stdint.h>

enum INPUT_SEL_POSITIVE {
    POSITIVE_AIN1 = 0b0001,
    POSITIVE_AIN2 = 0b0010,
    POSITIVE_AIN3 = 0b0011,
    POSITIVE_AIN4 = 0b0100,
    POSITIVE_AIN5 = 0b0101,
    POSITIVE_AIN6 = 0b0110,
    POSITIVE_AIN7 = 0b0111,
    POSITIVE_AIN8 = 0b0000,
    POSITIVE_AINCOM = 0b1000,
};

enum INPUT_SEL_NEGATIVE {
    NEGATIVE_AIN1 = 0b0001,
    NEGATIVE_AIN2 = 0b0010,
    NEGATIVE_AIN3 = 0b0011,
    NEGATIVE_AIN4 = 0b0100,
    NEGATIVE_AIN5 = 0b0101,
    NEGATIVE_AIN6 = 0b0110,
    NEGATIVE_AIN7 = 0b0111,
    NEGATIVE_AIN8 = 0b0000,
    NEGATIVE_AINCOM = 0b1000,
};
