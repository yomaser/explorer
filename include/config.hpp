#pragma once

#include <stdint.h>

// 滤波器使能
#define FILTER_ENABLE 0
// ADS1115 I2C 地址
#define ADS1115_ADDRESS 0x48
// 数据帧长度
#define FRAME_LENGTH 100
// 采样间隔
#define SAMPLE_INTERVAL 0
// 采样窗口大小
#define WINDOW_SIZE 5

// 检波器电压值
struct Geophone {
    int32_t Vertical[FRAME_LENGTH];
};