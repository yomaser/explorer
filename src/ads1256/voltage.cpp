#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Get voltage from ADC
double ADS1256::getVoltage(int32_t value) {
    // if the 24th bit (sign) is not 0, the number is negative
    if (value >> 23) {
        // conversion for the negative sign "mirroring" around zero
        value -= 16777216;
    }

    // 2.5 = Vref; 8388607 = 2^{23} - 1
    double voltage = ((2 * VREF) / 8388607) * value;
    return voltage;
}
