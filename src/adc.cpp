#include "adc.hpp"

ADS1115::ADS1115(uint8_t address) {
    this->address = address;
}

void ADS1115::begin() {
    Wire.begin();
    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(0x01);
    Wire.write(0xc0);
    Wire.write(0x83);
    Wire.endTransmission();
}

int32_t ADS1115::getVoltage() {
    Wire.beginTransmission(ADC_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(ADC_ADDRESS, 2);
    if (Wire.available() == 2) {
        int32_t value = Wire.read() << 8 | Wire.read();
        return value;
    }

    return 0;
}