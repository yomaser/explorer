#include "ads1256/sample.hpp"
#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Set ADC sample rate
void ADS1256::setSample(enum SAMPLE_RATE_SPS rate) {
    writeRegister(REGISTER_DRATE, rate);
}