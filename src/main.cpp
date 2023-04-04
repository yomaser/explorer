#include <Arduino.h>
#include <Wire.h>

#include "adc.hpp"
#include "config.hpp"
#include "filter.hpp"

void setup() {
    Serial.begin(115200);
    adcInit();
}

void loop() {
    Geophone geophone;
    uint8_t header[] = {
        FRAME_START,
        FRAME_HEAD,
    };

    for (uint8_t i = 0; i < DATA_LENGTH; i++) {
#if FILTER_ENABLE == 1
        filterValue(&geophone, i);
#else
        geophone.Vertical[i] = adcRead();
        if (SAMPLE_INTERVAL > 0) {
            delayMicroseconds(SAMPLE_INTERVAL);
        }
#endif
    }

    geophone.Altitude = 20.0;
    geophone.Latitude = 30.0;
    geophone.Longitude = 40.0;

    Serial.write(header, sizeof(header));
    Serial.write((uint8_t*)&geophone, sizeof(geophone));
}
