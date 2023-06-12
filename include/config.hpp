#pragma once

#include <stdint.h>
#include "ads1256/gain.hpp"

// 串口波特率
#define SERIAL_BAUD 921600
// #define SERIAL_BAUD 19200
// 采样率（单位 Sps）
#define SAMPLE_RATE 375
// #define SAMPLE_RATE 10
// ADC 测量增益
#define ADC_PRECISION GAIN_AMP_2X
// 数据帧起始字节
const uint8_t FRAME_HEADER[] = {0xAA, 0x55};

// 检波器数据帧
struct SensorData {
    double Vertical[SAMPLE_RATE];
    double EastWest[SAMPLE_RATE];
    double NorthSouth[SAMPLE_RATE];
    uint8_t Checksum[3];
};
