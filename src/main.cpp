#include <Arduino.h>

#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/sample.hpp"
#include "checksum.hpp"
#include "config.hpp"

ADS1256 adc(SS, PA3, PA2);

void setup() {
    Serial.begin(SERIAL_BAUD);
    adc.begin();

    adc.setGain(ADC_PRECISION);
    adc.setSample(SAMPLE_RATE_30000);
}

void loop() {
    SensorData sensorData;
    int32_t adcRawData;

    // Get voltage data
    for (uint16_t i = 0; i < SAMPLE_RATE; i++) {
        // Vertical geophone
        adcRawData = adc.getDifferential(POSITIVE_AIN1, NEGATIVE_AIN2);
        sensorData.Vertical[i] = adc.getVoltage(adcRawData);

        // East-West geophone
        adcRawData = adc.getDifferential(POSITIVE_AIN3, NEGATIVE_AIN4);
        sensorData.EastWest[i] = adc.getVoltage(adcRawData);

        // North-South geophone
        adcRawData = adc.getDifferential(POSITIVE_AIN5, NEGATIVE_AIN6);
        sensorData.NorthSouth[i] = adc.getVoltage(adcRawData);
    }

    // Get checksum
    for (uint8_t i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                sensorData.Checksum[0] =
                    getChecksum(sensorData.Vertical, SAMPLE_RATE);
                break;
            case 1:
                sensorData.Checksum[1] =
                    getChecksum(sensorData.EastWest, SAMPLE_RATE);
                break;
            case 2:
                sensorData.Checksum[2] =
                    getChecksum(sensorData.NorthSouth, SAMPLE_RATE);
                break;
        }
    }

    // Send structed data
    Serial.write(FRAME_HEADER, sizeof(FRAME_HEADER));
    delayMicroseconds(10);
    Serial.write((uint8_t*)&sensorData, sizeof(sensorData));
    Serial.flush();
}
