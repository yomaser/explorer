#pragma once

#include <stdint.h>

// 串口波特率
#define SERIAL_BAUD 19200
// ADS1115 I2C 地址
#define ADC_ADDRESS 0x48
// 采样率（单位 Sps）
#define SAMPLE_RATE 57
// ADS1115 测量精度（0 为最大增益）
#define ADC_PRECISION 0
// 数据帧起始字节
const uint8_t FRAME_HEADER[] = {0xAA, 0x55};

// 检波器数据帧
struct SensorData {
    float Vertical[SAMPLE_RATE];
    float EastWest[SAMPLE_RATE];
    float NorthSouth[SAMPLE_RATE];
};
