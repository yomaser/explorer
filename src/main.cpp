#include <Arduino.h>
#include <Wire.h>

#include "adc.hpp"
#include "config.hpp"
#include "gnss.hpp"

GNSS gnss(GNSS_TX, GNSS_RX, GNSS_BAUD);
ADS1115 ads1115(ADC_ADDRESS);

#if FILTER_ENABLE == 1
void filterValue(Geophone* phone, uint8_t index) {
    int32_t values[WINDOW_SIZE];
    int32_t filteredValue = 0;

    for (uint8_t i = 0; i < WINDOW_SIZE; i++) {
        values[i] = ads1115.getVoltage();

        for (uint8_t j = 0; j < i; j++) {
            if (values[i] < values[j]) {
                int32_t temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }

        if (WINDOW_SIZE / 2 == i) {
            filteredValue = values[i];
        }
    }

    phone->Vertical[index] = filteredValue;
}
#endif

void setup() {
    Serial.begin(115200);
    ads1115.begin();
    gnss.begin();
}

void loop() {
    Geophone geophone = {
        .Latitude = -1.0,
        .Longitude = -1.0,
        .Altitude = -1.0,
    };
    uint8_t header[] = {
        FRAME_START,
        FRAME_HEAD,
    };

    for (uint8_t i = 0; i < DATA_LENGTH; i++) {
#if FILTER_ENABLE == 1
        filterValue(&geophone, i);
#else
        geophone.Vertical[i] = ads1115.getVoltage();
        if (SAMPLE_INTERVAL > 0) {
            delayMicroseconds(SAMPLE_INTERVAL);
        }
#endif
    }

    if (millis() % 600000 == 0) {
        gnss.getCoordination(&geophone);
    }

    Serial.write(header, sizeof(header));
    Serial.write((uint8_t*)&geophone, sizeof(geophone));
}
