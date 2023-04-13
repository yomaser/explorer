#include <Arduino.h>
#include <Wire.h>

#include "adc.hpp"
#include "config.hpp"
#include "gnss.hpp"

uint8_t isRequest(uint8_t* array, size_t length);

GNSS gnss(GNSS_TX, GNSS_RX, GNSS_BAUD);
ADS1115 ads1115(ADC_ADDRESS);

Geophone geophone = {
    .Latitude = -1.0,
    .Longitude = -1.0,
    .Altitude = -1.0,
};

void setup() {
    Serial.begin(19200);
    ads1115.begin();
    gnss.begin();
}

void loop() {
    if (millis() % 600000 == 0) {
        gnss.getCoordination(&geophone);
    }

    if (isRequest((uint8_t*)FRAME_REQUEST, sizeof(FRAME_REQUEST))) {
        geophone.Vertical = ads1115.readADC(FS_1_024V, CHANNEL_AIN0);
        geophone.EastWest = ads1115.readADC(FS_1_024V, CHANNEL_AIN1);
        geophone.NorthSouth = ads1115.readADC(FS_1_024V, CHANNEL_AIN2);

        Serial.write(FRAME_HEADER, sizeof(FRAME_HEADER));
        Serial.write((uint8_t*)&geophone, sizeof(geophone));
        Serial.write(FRAME_TAIL, sizeof(FRAME_TAIL));
    }
}

uint8_t isRequest(uint8_t* array, size_t length) {
    size_t count = 0;

    while (count < length) {
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