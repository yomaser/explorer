#include "checksum.hpp"

uint8_t getChecksum(double arr[], uint16_t length) {
    uint16_t sum = 0;

    for (uint16_t i = 0; i < length; i++) {
        uint8_t* byteArr = reinterpret_cast<uint8_t*>(&arr[i]);

        for (uint8_t j = 0; j < sizeof(double); j++) {
            sum += byteArr[j];
        }
    }

    return (uint8_t)(sum % 256);
}