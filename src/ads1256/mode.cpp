#include "ads1256/mode.hpp"
#include "ads1256/adc.hpp"
#include "ads1256/command.hpp"

// Set ADC read mode
void ADS1256::setMode(enum ADC_MODE mode) {
    SPI.beginTransaction(SPISettings(SPEED, MSBFIRST, SPI_MODE1));
    // Select chip
    digitalWrite(_cs_pin, LOW);
    if (mode != ADC_MODE_CONTINUOUS) {
        // Issue SDATAC command
        SPI.transfer(COMMAND_SDATAC);
    }
    // Issue RDATAC command
    SPI.transfer(COMMAND_RDATAC);
    // Deselect chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();
}
