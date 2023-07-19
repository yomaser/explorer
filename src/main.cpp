#include <Arduino.h>

#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/gain.hpp"
#include "ads1256/sample.hpp"

#include "blink.hpp"
#include "checksum.hpp"
#include "config.hpp"

ADS1256 adc(SS, PA3, PA2);

int32_t getRawValue(int32_t value) {
    if (value >> 23) {
        value -= 16777216;
    }

    return value;
}

uint8_t isReset() {
    uint8_t gain = adc.getGain();
    uint8_t sample = adc.getSample();
    if (gain != GAIN_AMP || sample != SAMPLE_RATE) {
        return 1;
    }

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
    blinkLED(3, 50);

    initADC();
    blinkLED(5, 50);
}

void loop() {
    SensorData sensorData;

    // Get voltage data
    for (uint16_t i = 0; i < PACKET_SIZE; i++) {
        // Support runtime reset
        if (isReset()) {
            initADC();
            blinkLED(1, 50);

            Serial.write(ACK_WORD, sizeof(ACK_WORD));
            Serial.flush();
        }

        // Vertical geophone (EHZ)
        sensorData.EHZ[i] =
            getRawValue(adc.getDifferential(INPUT_AIN1, INPUT_AINCOM));
        adc.getDifferential(INPUT_AIN2, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN3, INPUT_AINCOM);

        // East-West geophone (EHE)
        sensorData.EHE[i] =
            getRawValue(adc.getDifferential(INPUT_AIN4, INPUT_AINCOM));
        adc.getDifferential(INPUT_AIN5, INPUT_AINCOM);
        adc.getDifferential(INPUT_AIN6, INPUT_AINCOM);

        // North-South geophone (EHN)
        sensorData.EHN[i] =
            getRawValue(adc.getDifferential(INPUT_AIN7, INPUT_AINCOM));
        adc.getDifferential(INPUT_AIN8, INPUT_AINCOM);
    }

    // Get checksum
    sensorData.Checksum[0] = getChecksum(sensorData.EHZ, PACKET_SIZE);
    sensorData.Checksum[1] = getChecksum(sensorData.EHE, PACKET_SIZE);
    sensorData.Checksum[2] = getChecksum(sensorData.EHN, PACKET_SIZE);

    // Send syncing word
    Serial.write(SYNC_WORD, sizeof(SYNC_WORD));
    delayMicroseconds(5);

    // Send struct data
    Serial.write((uint8_t*)&sensorData, sizeof(sensorData));
    Serial.flush();
}
