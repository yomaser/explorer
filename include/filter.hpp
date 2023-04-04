#pragma once

#include <Arduino.h>
#include <stdint.h>
#include "adc.hpp"
#include "config.hpp"

void filterValue(Geophone* phone, uint8_t index);