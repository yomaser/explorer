#include "ads1256/adc.hpp"
#include "ads1256/register.hpp"

// Wait for DRDY to go low, then read register
void ADS1256::wait() {
    // Stuck unless DRDY is low
    while (digitalRead(_drdy_pin)) {
        delayMicroseconds(5);
    }
}

// Begin SPI communication
void ADS1256::begin() {
    // Set pin mode
    pinMode(_cs_pin, OUTPUT);
    pinMode(_drdy_pin, INPUT);
    pinMode(_rst_pin, OUTPUT);
    // Hard reset ADS1256
    digitalWrite(_rst_pin, LOW);
    delay(250);
    digitalWrite(_rst_pin, HIGH);
    delay(250);
    // Initialize SPI
    SPI.begin();
    // Select chip
    digitalWrite(_cs_pin, LOW);
    // Enable calibration
    writeRegister(ADC_REGISTER_STATUS, 0x04);
}
