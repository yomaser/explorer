#pragma once

#include <stdint.h>

typedef enum {
    DEVICE_COMMAND_WAKEUP = 0x00,
    DEVICE_COMMAND_RDATA = 0x01,
    DEVICE_COMMAND_RDATAC = 0x03,
    DEVICE_COMMAND_SDATAC = 0x0F,
    DEVICE_COMMAND_RREG = 0x10,
    DEVICE_COMMAND_WREG = 0x50,
    DEVICE_COMMAND_SELFCAL = 0xF0,
    DEVICE_COMMAND_SELFOCAL = 0xF1,
    DEVICE_COMMAND_SELFGCAL = 0xF2,
    DEVICE_COMMAND_SYSOCAL = 0xF3,
    DEVICE_COMMAND_SYSGCAL = 0xF4,
    DEVICE_COMMAND_SYNC = 0xFC,
    DEVICE_COMMAND_STANDBY = 0xFD,
    DEVICE_COMMAND_RESET = 0xFE,
} DeviceCommand;
