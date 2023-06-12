#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/command.hpp"
#include "ads1256/register.hpp"

int32_t ADS1256::getDifferential(uint8_t positiveCh, uint8_t negativeCh) {
    wait();
    SPI.beginTransaction(SPISettings(SPEED, MSBFIRST, SPI_MODE1));

    // CS must stay LOW during the entire
    digitalWrite(_cs_pin, LOW);
    SPI.transfer(COMMAND_WREG | REGISTER_MUX);
    SPI.transfer(0x00);

    // Write the positive and negative channels to MUX
    SPI.transfer((positiveCh << 4) | negativeCh);

    // Request a conversion
    SPI.transfer(COMMAND_SYNC);
    delayMicroseconds(4);
    SPI.transfer(COMMAND_WAKEUP);
    SPI.transfer(COMMAND_RDATA);
    delayMicroseconds(5);

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