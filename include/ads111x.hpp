#pragma once

#include <Wire.h>
#include "config.hpp"

void adcInit();
int32_t adcRead();