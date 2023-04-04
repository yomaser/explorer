#pragma once

#include <Wire.h>
#include "config.hpp"

class ADS1115 {
   private:
    uint8_t address;

   public:
    ADS1115(uint8_t address);
    void begin();
    int32_t getVoltage();
};
