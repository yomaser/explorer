#pragma once

#include <stdint.h>

// GNSS 模块 TX 管脚
#define GNSS_TX 2
// GNSS 模块 RX 管脚
#define GNSS_RX 3
// GNSS 模块波特率
#define GNSS_BAUD 9600
// 采样间隔
#define SAMPLE_INTERVAL 0
// 采样窗口大小
#define WINDOW_SIZE 10
// ADS1115 I2C 地址
#define ADC_ADDRESS 0x48
// ADS1115 测量精度
#define ADC_PRECISION 16

// 数据帧索取字节
const uint8_t FRAME_REQUEST[] = {0x55, 0x55};
// 数据帧起始字节
const uint8_t FRAME_HEADER[] = {0x55, 0xAA};

// 检波器数据
struct Geophone {
    float Latitude;
    float Longitude;
    float Altitude;
    float Vertical;
    float EastWest;
    float NorthSouth;
};
