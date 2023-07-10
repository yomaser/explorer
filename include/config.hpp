#pragma once

#include <stdint.h>
#include "ads1256/gain.hpp"
#include "ads1256/sample.hpp"

// ADC 增益放大倍率
#define GAIN_AMP GAIN_AMP_4X  // maximum GAIN_AMP_64X
// ADC 采样率大小
#define SAMPLE_RATE SAMPLE_RATE_1000  // maximum SAMPLE_RATE_30000
// 数据帧内检波器报文长度
#define PACKET_SIZE 10  // maximum 375
// TTL/485 串口波特率
#define SERIAL_BAUD 19200  // maximum 921600
// 设备复位字节
#define RESET_WORD 0x61

// 数据帧同步字节
const uint8_t SYNC_WORD[] = {
    0xAA,
    0x55,
};
// 下位机应答字节
const uint8_t ACK_WORD[] = {
    0xAC,
    0x55,
};

// 检波器数据帧格式
struct SensorData {
    int32_t EHZ[PACKET_SIZE]; // 垂直
    int32_t EHE[PACKET_SIZE]; // 东西
    int32_t EHN[PACKET_SIZE]; // 南北
    uint8_t Checksum[3];
};
