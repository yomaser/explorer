#include <Arduino.h>
#include <Wire.h>
#include "ads111x.hpp"
#include "config.hpp"
#include "filter.hpp"

void setup() {
    Serial.begin(115200);
    adcInit();
}

void loop() {
    Geophone geophone;

    for (uint8_t i = 0; i < FRAME_LENGTH; i++) {
#if FILTER_ENABLE == 1
        filterValue(&geophone, i);
#else
        geophone.Vertical[i] = adcRead();
        if (SAMPLE_INTERVAL > 0) {
            delayMicroseconds(SAMPLE_INTERVAL);
        }
#endif
    }

    Serial.write((uint8_t*)&geophone, sizeof(geophone));
}
