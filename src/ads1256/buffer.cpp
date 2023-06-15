#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Set analog input buffer
void ADS1256::setBuffer(uint8_t enable) {
    writeRegister(REGISTER_STATUS, enable ? 0b00000110 : 0b00000100);
}