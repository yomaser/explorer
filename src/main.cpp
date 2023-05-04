#include <Arduino.h>

#define PT_USE_TIMER
#define PT_USE_SEM

#include "ADS1X15.h"
#include "config.hpp"
#include "pt.h"

ADS1115 ads(ADC_ADDRESS);
SensorData sensorData;

static struct pt ThreadSerialListener;
static struct pt ThreadGeophoneReader;

void setup() {
    PT_INIT(&ThreadSerialListener);
    PT_INIT(&ThreadGeophoneReader);
}

uint8_t isRequest(uint8_t* array, size_t length) {
    uint64_t start = millis();
    size_t counter = 0;

    while (millis() - start < TIMEOUT_MS && counter < length) {
        if (Serial.available()) {
            uint8_t byte = Serial.read();

            if (byte == array[counter]) {
                counter++;
            } else {
                counter = 0;
            }

            if (counter == length) {
                Serial.flush();
                return 1;
            }
        }
    }

    return 0;
}

static int SerialListener(struct pt* pt) {
    PT_BEGIN(pt);

    Serial.begin(SERIAL_BAUD);
    while (1) {
        if (isRequest((uint8_t*)FRAME_REQUEST, sizeof(FRAME_REQUEST))) {
            Serial.write(FRAME_HEADER, sizeof(FRAME_HEADER));
            PT_YIELD(pt);
            Serial.write((uint8_t*)&sensorData, sizeof(sensorData));
        } else {
            Serial.write(FRAME_PADDING);
        }

        Serial.flush();
        PT_YIELD(pt);
    }

    PT_END(pt);
}

uint16_t getDelay(uint8_t sample) {
    if (sample == 0) {
        return 0;
    }

    return 1000 / sample;
}

static int GeophoneReader(struct pt* pt) {
    PT_BEGIN(pt);

    ads.begin();
    while (1) {
        for (uint8_t i = 0; i < SAMPLE_RATE; i++) {
            ads.setGain(ADC_PRECISION);
            float f = ads.toVoltage(1);

            sensorData.Vertical[i] = (float)ads.readADC(0) * f;
            sensorData.EastWest[i] = (float)ads.readADC(1) * f;
            sensorData.NorthSouth[i] = (float)ads.readADC(2) * f;

            PT_TIMER_DELAY(pt, getDelay(SAMPLE_RATE));
            PT_YIELD(pt);
        }
    }

    PT_END(pt);
}

void loop() {
    SerialListener(&ThreadSerialListener);
    GeophoneReader(&ThreadGeophoneReader);
}
