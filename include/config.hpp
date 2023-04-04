#pragma once

#include <stdint.h>

// 滤波器使能
#define FILTER_ENABLE 0
// ADS1115 I2C 地址
#define ADS1115_ADDRESS 0x48
// 数据帧起始字节
#define FRAME_START 0x55
// 数据帧头字节
#define FRAME_HEAD 0xAA
// 检波器数据长度
#define DATA_LENGTH 100
// 采样间隔
#define SAMPLE_INTERVAL 0
// 采样窗口大小
#define WINDOW_SIZE 5

// 检波器电压值
struct Geophone {
    float Latitude;
    float Longitude;
    float Altitude;
    int32_t Vertical[DATA_LENGTH];
};