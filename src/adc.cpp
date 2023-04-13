#include "adc.hpp"

ADS1115::ADS1115(uint8_t address) {
    this->address = address;
}

void ADS1115::begin() {
    Wire.begin();
}

float ADS1115::readADC(uint8_t gain, uint8_t channel) {
    // 配置寄存器
    Wire.beginTransmission(this->address);
    Wire.write(0x01);

    // 选择通道和增益
    Wire.write(channel << 4 | 0x83 | gain);
    Wire.endTransmission();

    // 读取16位的原始值
    Wire.requestFrom(this->address, (uint8_t)2);
    while (Wire.available() < 2) {
        ;
    }
    int16_t raw = Wire.read() << 8 | Wire.read();

    // 原始值转电压值
    float voltage;
    switch (gain) {
        case FS_6_144V:
            // +/-6.144V 量程各 LSB 值为 0.1875mV
            voltage = raw * 0.1875 / 1000.0;
            break;
        case FS_4_096V:
            // +/-4.096V 量程各 LSB 值为 0.125mV
            voltage = raw * 0.125 / 1000.0;
            break;
        case FS_2_048V:
            // +/-2.048V 量程各 LSB 值为 0.0625mV
            voltage = raw * 0.0625 / 1000.0;
            break;
        case FS_1_024V:
            // +/-1.024V 量程各 LSB 值为 0.03125mV
            voltage = raw * 0.03125 / 1000.0;
            break;
        case FS_0_512V:
            // +/-0.512V 量程各 LSB 值为 0.015625mV
            voltage = raw * 0.015625 / 1000.0;
            break;
        case FS_0_256V:
            // +/-0.256V 量程各 LSB 值为 0.0078125mV
            voltage = raw * 0.0078125 / 1000.0;
            break;
        default:
            voltage = 0.0;
            break;
    }

    return voltage;
}
