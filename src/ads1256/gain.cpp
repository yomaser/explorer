#include "ads1256/gain.hpp"
#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Set ADC gain
void ADS1256::setGain(enum GAIN_AMP_RATE gain) {
    writeRegister(REGISTER_ADCON, gain & 0b111);
}