#include <Arduino.h>

#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/gain.hpp"
#include "ads1256/sample.hpp"

#include "blink.hpp"
#include "checksum.hpp"
#include "config.hpp"

ADS1256 adc(SS, PA3, PA2);

uint8_t isReset() {
    return Serial.available() && Serial.read() == RESET_WORD;
}

void initADC() {
    adc.begin();
    adc.reset();

    adc.setGain(GAIN_AMP);
    adc.setSample(SAMPLE_RATE);
    adc.setStatus(ENABLE, DISABLE);
}

void setup() {
    Serial.begin(SERIAL_BAUD);
    blinkLED(3, 100);

    initADC();
    blinkLED(5, 100);
}

void loop() {
    SensorData sensorData;

    // Get voltage data
    for (uint16_t i = 0; i < PACKET_SIZE; i++) {
        // Support runtime reset
        if (isReset()) {
            initADC();
            blinkLED(1, 100);

            Serial.write(ACK_WORD, sizeof(ACK_WORD));
            Serial.flush();
        }

        // Vertical geophone (EHZ)
        sensorData.EHZ[i] = adc.getDifferential(INPUT_AIN1, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN2, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN3, INPUT_AINCOM);

        // East-West geophone (EHE)
        sensorData.EHE[i] = adc.getDifferential(INPUT_AIN4, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN5, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN6, INPUT_AINCOM);

        // North-South geophone (EHN)
        sensorData.EHN[i] = adc.getDifferential(INPUT_AIN7, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN8, INPUT_AINCOM);
    }

    // Get checksum
    for (uint8_t i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                sensorData.Checksum[0] =
                    getChecksum(sensorData.EHZ, PACKET_SIZE);
                break;
            case 1:
                sensorData.Checksum[1] =
                    getChecksum(sensorData.EHE, PACKET_SIZE);
                break;
            case 2:
                sensorData.Checksum[2] =
                    getChecksum(sensorData.EHN, PACKET_SIZE);
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
