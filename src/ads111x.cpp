#include <ads111x.hpp>

void adcInit() {
    Wire.begin();
    Wire.beginTransmission(ADS1115_ADDRESS);
    Wire.write(0x01);
    Wire.write(0xc0);
    Wire.write(0x83);
    Wire.endTransmission();
}

int32_t adcRead() {
    Wire.beginTransmission(ADS1115_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(ADS1115_ADDRESS, 2);
    if (Wire.available() == 2) {
        int32_t value = Wire.read() << 8 | Wire.read();
        return value;
    }

    return 0;
}