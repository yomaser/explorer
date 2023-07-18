#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Set analog input buffer and calibration
void ADS1256::setStatus(uint8_t buffer, uint8_t calibration) {
    writeRegister(REGISTER_STATUS, (buffer << 1) | buffer << 2);
}
