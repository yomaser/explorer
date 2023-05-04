#pragma once

#include <stdint.h>

// 串口波特率
#define SERIAL_BAUD 19200
// ADS1115 I2C 地址
#define ADC_ADDRESS 0x48
// ADS1115 测量精度
#define ADC_PRECISION 0
// 请求字节等待超时
#define TIMEOUT_MS 100
// 采样率（单位 Sps）
#define SAMPLE_RATE 20

// 数据帧填充字节
const uint8_t FRAME_PADDING = 0x56;
// 数据帧请求字节
const uint8_t FRAME_REQUEST[] = {0x55, 0x55};
// 数据帧起始字节
const uint8_t FRAME_HEADER[] = {0x55, 0xAA};

// 检波器数据帧
struct SensorData {
    float Vertical;
    float EastWest;
    float NorthSouth;
};
