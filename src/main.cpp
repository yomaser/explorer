#include <Arduino.h>
#include <Wire.h>

#include "ADS1X15.h"
#include "config.hpp"

ADS1115 ads(ADC_ADDRESS);

uint8_t isRequest(uint8_t* array, size_t length) {
    size_t count = 0;
    uint32_t start = millis();

    while (millis() - start < TIMEOUT_MS && count < length) {
        if (Serial.available()) {
            uint8_t byte = Serial.read();

            if (byte == array[count]) {
                count++;
            } else {
                count = 0;
            }

            if (count == length) {
                return 1;
            }
        }
    }

    return 0;
}

void setup() {
    Serial.begin(19200);
    ads.begin();
}

void loop() {
    if (isRequest((uint8_t*)FRAME_REQUEST, sizeof(FRAME_REQUEST))) {
        ads.setGain(ADC_PRECISION);
        float f = ads.toVoltage(1);
        DataFrame dataFrame = {
            .Vertical = (float)ads.readADC(0) * f,
            .EastWest = (float)ads.readADC(1) * f,
            .NorthSouth = (float)ads.readADC(2) * f,
        };

        Serial.write(FRAME_HEADER, sizeof(FRAME_HEADER));
        delayMicroseconds(500);
        Serial.write((uint8_t*)&dataFrame, sizeof(dataFrame));
    } else {
        Serial.write(FRAME_PADDING);
    }

    delayMicroseconds(500);
    Serial.flush();
}
