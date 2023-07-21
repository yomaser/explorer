#pragma once

#include <stdint.h>
#include "ads1256/gain.hpp"
#include "ads1256/sample.hpp"

// ADC gain amplifier factor
#define GAIN_AMP GAIN_AMP_1X  // maximum GAIN_AMP_64X
// ADC sampling rate
#define SAMPLE_RATE SAMPLE_RATE_2000  // maximum SAMPLE_RATE_30000
// Data packet size
#define PACKET_SIZE 10  // maximum 375
// TTL/485 serial baud rate
#define SERIAL_BAUD 19200  // maximum 921600
// Reset word
#define RESET_WORD 0x61

// Syncing bytes
const uint8_t SYNC_WORD[] = {
    0xFC,
    0x1B,
};
// Responding bytes
const uint8_t ACK_WORD[] = {
    0xFC,
    0x2B,
};

// Geophone data frame format
typedef struct {
    int32_t EHZ[PACKET_SIZE];  // Vertical
    int32_t EHE[PACKET_SIZE];  // East-West
    int32_t EHN[PACKET_SIZE];  // North-South
    uint8_t Checksum[3];
} sensor_t;
