#include "ads1256/adc.hpp"
#include "ads1256/command.hpp"

// Soft reset ADS1256 module
void ADS1256::reset() {
    SPI.beginTransaction(SPISettings(SPEED, MSBFIRST, SPI_MODE1));
    // Select chip
    digitalWrite(_cs_pin, LOW);
    // Wait a moment
    delayMicroseconds(10);
    // Send reset command
    SPI.transfer(DEVICE_COMMAND_RESET);
    // Wait for reset to complete
    delay(2);
    // Issue SDATAC
    SPI.transfer(DEVICE_COMMAND_SDATAC);
    delayMicroseconds(100);
    // Deselect chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();
}
