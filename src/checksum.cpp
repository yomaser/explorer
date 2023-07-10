#include "checksum.hpp"

uint8_t getChecksum(int32_t arr[], uint16_t length) {
    uint16_t sum = 0;

    for (uint16_t i = 0; i < length; i++) {
        uint8_t* byteArr = reinterpret_cast<uint8_t*>(&arr[i]);

        for (uint8_t j = 0; j < sizeof(int32_t); j++) {
            sum += byteArr[j];
        }
    }

    return (uint8_t)(sum % 256);
}