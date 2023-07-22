#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/command.hpp"
#include "ads1256/register.hpp"

// One Shot single channel mode, use with setChannel()
int32_t ADS1256::getSingleOneShot() {
    wait();
    SPI.beginTransaction(SPISettings(1920000, MSBFIRST, SPI_MODE1));

    // CS must stay LOW during the entire
    digitalWrite(_cs_pin, LOW);
    // Issue RDATA command
    SPI.transfer(DEVICE_COMMAND_RDATA);
    delayMicroseconds(10);

    // Get the 24-bit result
    int32_t result = (int32_t)SPI.transfer(DEVICE_COMMAND_SDATAC) << 16 |
                     (int32_t)SPI.transfer(DEVICE_COMMAND_SDATAC) << 8 |
                     (int32_t)SPI.transfer(DEVICE_COMMAND_SDATAC);

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
    int32_t result = (int32_t)SPI.transfer(DEVICE_COMMAND_SDATAC) << 16 |
                     (int32_t)SPI.transfer(DEVICE_COMMAND_SDATAC) << 8 |
                     (int32_t)SPI.transfer(DEVICE_COMMAND_SDATAC);

    // Deselect the chip
    digitalWrite(_cs_pin, HIGH);
    SPI.endTransaction();

    return result;
}
