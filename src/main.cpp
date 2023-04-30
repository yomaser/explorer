#include <Arduino.h>
#include <Wire.h>

#include "ADS1X15.h"
#include "config.hpp"
#include "gnss.hpp"

uint8_t isRequest(uint8_t* array, size_t length);

// GNSS gnss(GNSS_TX, GNSS_RX, GNSS_BAUD);
ADS1115 ads(ADC_ADDRESS);

Geophone geophone = {
    .Latitude = -1.0,
    .Longitude = -1.0,
    .Altitude = -1.0,
};

void setup() {
    Serial.begin(19200);
    // gnss.begin();
    ads.begin();
}

void loop() {
    // if (millis() % 600000 == 0) {
    //     gnss.getCoordination(&geophone);
    // }

    if (isRequest((uint8_t*)FRAME_REQUEST, sizeof(FRAME_REQUEST))) {
        ads.setGain(ADC_PRECISION);
        float f = ads.toVoltage(1);

        geophone.Vertical = (float)ads.readADC(0) * f;
        geophone.EastWest = (float)ads.readADC(1) * f;
        geophone.NorthSouth = (float)ads.readADC(2) * f;

        Serial.write(FRAME_HEADER, sizeof(FRAME_HEADER));
        delayMicroseconds(500);
        Serial.write((uint8_t*)&geophone, sizeof(geophone));
        delayMicroseconds(500);
    } else {
        Serial.write(0x56);
        delayMicroseconds(500);
    }

    Serial.flush();
}

uint8_t isRequest(uint8_t* array, size_t length) {
    size_t count = 0;
    uint32_t start = millis();

    while (millis() - start < TIMEOUT_MS && count < length) {
        if (Serial.available()) {
            uint8_t byte;
            Serial.readBytes(&byte, 1);

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
