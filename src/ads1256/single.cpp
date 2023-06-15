#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/command.hpp"
#include "ads1256/register.hpp"

// Single channel mode, use with setChannel()
int32_t ADS1256::getSingleChannel() {
    wait();
    SPI.beginTransaction(SPISettings(1920000, MSBFIRST, SPI_MODE1));

    // CS must stay LOW during the entire
    digitalWrite(_cs_pin, LOW);
    // Issue RDATA command
    SPI.transfer(COMMAND_RDATA);
    delayMicroseconds(10);

    // Get the 24-bit result
    int32_t result = SPI.transfer(0x0F);
    result <<= 8;                  // MSB gets shifted LEFT by 8 bits
    result |= SPI.transfer(0x0F);  // MSB | Mid-byte
    result <<= 8;                  // MSB | Mid-byte gets shifted LEFT by 8 bits
    result |= SPI.transfer(0x0F);  //(MSB | Mid-byte) | LSB - final result

    // Deselect the chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();

    return result;
}

// Continuous resding mode (i.e. AIN0+COM)
int32_t ADS1256::getSingleContinuous() {
    wait();
    SPI.beginTransaction(SPISettings(1920000, MSBFIRST, SPI_MODE1));

    // CS must stay LOW during the entire
    digitalWrite(_cs_pin, LOW);

    // Get the 24-bit result
    int32_t result = SPI.transfer(0x0F);
    result <<= 8;                  // MSB gets shifted LEFT by 8 bits
    result |= SPI.transfer(0x0F);  // MSB | Mid-byte
    result <<= 8;                  // MSB | Mid-byte gets shifted LEFT by 8 bits
    result |= SPI.transfer(0x0F);  //(MSB | Mid-byte) | LSB - final result

    // Deselect the chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();

    return result;
}