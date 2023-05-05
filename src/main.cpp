#include <Arduino.h>

#include "ADS1X15.h"
#include "config.hpp"

ADS1115 ads(ADC_ADDRESS);
SensorData sensorData;

void setup() {
    Serial.begin(SERIAL_BAUD);
    ads.begin();
}

void loop() {
    ads.setGain(ADC_PRECISION);
    float f = ads.toVoltage(1);

    for (uint8_t i = 0; i < SAMPLE_RATE; i++) {
        sensorData.Vertical[i] = (float)ads.readADC(0) * f;
        sensorData.EastWest[i] = (float)ads.readADC(1) * f;
        sensorData.NorthSouth[i] = (float)ads.readADC(2) * f;
    }

    Serial.write(FRAME_HEADER, sizeof(FRAME_HEADER));
    delayMicroseconds(1000);
    Serial.write((uint8_t*)&sensorData, sizeof(sensorData));
    Serial.flush();
}
