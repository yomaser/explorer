#include <Arduino.h>

#define LENGTH 100
#define OFFSET 0

void setup() {
    pinMode(A0, INPUT);
    Serial.begin(115200);
}

struct Geophone {
    uint32_t Vertical[LENGTH];
} geophone;

void loop() {
    for (uint8_t i = 0; i < LENGTH; i++) {
        geophone.Vertical[i] = analogRead(A0) - OFFSET;
        delayMicroseconds(1000);
    }

    Serial.write((uint8_t*)&geophone, sizeof(geophone));
}