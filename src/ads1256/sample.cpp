#include "ads1256/sample.hpp"
#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

void ADS1256::setSample(uint8_t rate) {
    writeRegister(REGISTER_DRATE, rate);
}