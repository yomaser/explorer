#include "ads1256/adc.hpp"
#include "ads1256/channel.hpp"
#include "ads1256/register.hpp"

// Set single ended input channel
void ADS1256::setChannel(enum INPUT_SEL channel) {
    writeRegister(REGISTER_MUX, (channel << 4) | INPUT_AINCOM);
}