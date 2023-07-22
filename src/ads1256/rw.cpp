#include "ads1256/adc.hpp"
#include "ads1256/command.hpp"
#include "ads1256/register.hpp"

uint8_t ADS1256::readRegister(uint8_t reg) {
    wait();
    SPI.beginTransaction(SPISettings(SPEED, MSBFIRST, SPI_MODE1));
    // Select chip
    digitalWrite(_cs_pin, LOW);
    // 0x10 = RREG
    SPI.transfer(DEVICE_COMMAND_RREG | reg);
    SPI.transfer(DEVICE_COMMAND_WAKEUP);
    delayMicroseconds(5);
    // Get register value
    uint8_t result = SPI.transfer(0xFF);
    // Deselect chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();

    return result;
}

void ADS1256::writeRegister(uint8_t reg, uint8_t value) {
    wait();
    SPI.beginTransaction(SPISettings(SPEED, MSBFIRST, SPI_MODE1));
    // Select chip
    digitalWrite(_cs_pin, LOW);
    // 0x50 = WREG
    SPI.transfer(DEVICE_COMMAND_WREG | reg);
    SPI.transfer(DEVICE_COMMAND_WAKEUP);
    SPI.transfer(value);
    // Deselect chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();
}
