#include <Arduino.h>

#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/gain.hpp"
#include "ads1256/sample.hpp"

#include "blink.hpp"
#include "checksum.hpp"
#include "config.hpp"

ADS1256 adc(SS, PA3, PA2);

void setup() {
    Serial.begin(SERIAL_BAUD);
    blinkLED(3, 100);

    adc.begin();
    adc.setBuffer(true);
    adc.setGain(GAIN_AMP);
    adc.setSample(SAMPLE_RATE);

    delay(1000);
    adc.reset();
    blinkLED(5, 100);
}

void loop() {
    if (Serial.available() && Serial.read() == RESET_WORD) {
        adc.reset();
        blinkLED(1, 100);
        Serial.write(ACK_WORD, sizeof(ACK_WORD));
    }

    int32_t adcRawData;
    SensorData sensorData;

    // Get voltage data
    for (uint16_t i = 0; i < PACKET_SIZE; i++) {
        // Vertical geophone
        adcRawData = adc.getDifferential(INPUT_AIN1, INPUT_AINCOM);
        sensorData.Vertical[i] = adc.getVoltage(adcRawData);

        adcRawData = adc.getDifferential(INPUT_AIN2, INPUT_AINCOM);
        adcRawData = adc.getDifferential(INPUT_AIN3, INPUT_AINCOM);

        // East-West geophone
        adcRawData = adc.getDifferential(INPUT_AIN4, INPUT_AINCOM);
        sensorData.EastWest[i] = adc.getVoltage(adcRawData);

        adcRawData = adc.getDifferential(INPUT_AIN5, INPUT_AINCOM);
        adcRawData = adc.getDifferential(INPUT_AIN6, INPUT_AINCOM);

        // North-South geophone
        adcRawData = adc.getDifferential(INPUT_AIN7, INPUT_AINCOM);
        sensorData.NorthSouth[i] = adc.getVoltage(adcRawData);

        adcRawData = adc.getDifferential(INPUT_AIN8, INPUT_AINCOM);
    }

    // Get checksum
    for (uint8_t i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                sensorData.Checksum[0] =
                    getChecksum(sensorData.Vertical, PACKET_SIZE);
                break;
            case 1:
                sensorData.Checksum[1] =
                    getChecksum(sensorData.EastWest, PACKET_SIZE);
                break;
            case 2:
                sensorData.Checksum[2] =
                    getChecksum(sensorData.NorthSouth, PACKET_SIZE);
                break;
        }
    }

    // Send sync word
    Serial.write(SYNC_WORD, sizeof(SYNC_WORD));
    delayMicroseconds(5);
    // Send structed data
    Serial.write((uint8_t*)&sensorData, sizeof(sensorData));
    Serial.flush();
}
