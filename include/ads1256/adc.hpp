#pragma once

#include <SPI.h>
#include <stdint.h>

#define VREF 2.517
#define SPEED 1920000

class ADS1256 {
   private:
    uint8_t _cs_pin;
    uint8_t _drdy_pin;
    uint8_t _rst_pin;
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);

   public:
    ADS1256(uint8_t cs_pin, uint8_t drdy_pin, uint8_t rst_pin);
    void setMode(uint8_t mode);
    void setGain(uint8_t gain);
    void setSample(uint8_t rate);
    void setBuffer(uint8_t enable);
    void setChannel(uint8_t channel);
    int32_t getSingleChannel();
    int32_t getSingleContinuous();
    int32_t getDifferential(uint8_t positiveCh, uint8_t negativeCh);
    double getVoltage(int32_t value);
    void begin();
    void reset();
    void wait();
};
