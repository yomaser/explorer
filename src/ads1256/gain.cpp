#include "ads1256/gain.hpp"
#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

void ADS1256::setGain(uint8_t gain) {
    writeRegister(REGISTER_ADCON, gain & 0b111);
}