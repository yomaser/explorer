#pragma once

#include <SPI.h>
#include <stdint.h>

#include "ads1256/channel.hpp"
#include "ads1256/gain.hpp"
#include "ads1256/mode.hpp"
#include "ads1256/sample.hpp"

#define VREF 2.5
#define SPEED 1920000

#define ENABLE 1
#define DISABLE 0

class ADS1256 {
   private:
    uint8_t _cs_pin;
    uint8_t _drdy_pin;
    uint8_t _rst_pin;
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);

   public:
    ADS1256(uint8_t cs_pin, uint8_t drdy_pin, uint8_t rst_pin);
    void setMode(enum ADC_MODE mode);
    void setStatus(uint8_t buffer, uint8_t calibration);
    void setGain(enum GAIN_AMP_RATE gain);
    enum GAIN_AMP_RATE getGain();
    void setSample(enum SAMPLE_RATE_SPS rate);
    enum SAMPLE_RATE_SPS getSample();
    void setChannel(enum INPUT_SEL channel);
    enum INPUT_SEL getChannel();
    int32_t getSingleChannel();
    int32_t getSingleContinuous();
    int32_t getDifferential(enum INPUT_SEL positiveCh,
                            enum INPUT_SEL negativeCh);
    double getVoltage(int32_t value);
    void begin();
    void reset();
    void wait();
};
