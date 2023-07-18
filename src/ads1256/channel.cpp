#include "ads1256/channel.hpp"
#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Set single ended input channel
void ADS1256::setChannel(enum INPUT_SEL channel) {
    writeRegister(REGISTER_MUX, (channel << 4) | INPUT_AINCOM);
}

// Get single ended input channel
enum INPUT_SEL ADS1256::getChannel() {
    return (enum INPUT_SEL)(readRegister(REGISTER_MUX) >> 4);
}
