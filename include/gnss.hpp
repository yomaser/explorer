#pragma once

#ifdef ESP32
#include <EspSoftwareSerial.h>
#else
#include <SoftwareSerial.h>
#endif

#include <stdint.h>
#include "config.hpp"

class GNSS {
   private:
    SoftwareSerial* Serial;
    uint8_t rx, tx;
    uint16_t baud;

   public:
    GNSS(uint8_t rx, uint8_t tx, uint16_t baud);
    void begin();
    void getCoordination(Geophone* phone);
};
