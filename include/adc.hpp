#pragma once

#include <Wire.h>
#include "config.hpp"

#define CONFIG_REG 0x01  // ADC 配置寄存器

#define CHANNEL_AIN0 0x00  // 测量通道 AIN0
#define CHANNEL_AIN1 0x01  // 测量通道 AIN1
#define CHANNEL_AIN2 0x02  // 测量通道 AIN2
#define CHANNEL_AIN3 0x03  // 测量通道 AIN3

#define FS_6_144V 0x00  // 量程范围 +/-6.144V
#define FS_4_096V 0x02  // 量程范围 +/-4.096V
#define FS_2_048V 0x04  // 量程范围 +/-2.048V
#define FS_1_024V 0x06  // 量程范围 +/-1.024V
#define FS_0_512V 0x08  // 量程范围 +/-0.512V
#define FS_0_256V 0x0A  // 量程范围 +/-0.256V

class ADS1115 {
   private:
    uint8_t address;

   public:
    ADS1115(uint8_t address);
    void begin();
    float readADC(uint8_t gain, uint8_t channel);
};
