#include "filter.hpp"

void filterValue(Geophone* phone, uint8_t index) {
    int32_t values[WINDOW_SIZE];
    int32_t filteredValue = 0;

    for (uint8_t i = 0; i < WINDOW_SIZE; i++) {
        values[i] = adcRead();

        for (uint8_t j = 0; j < i; j++) {
            if (values[i] < values[j]) {
                int32_t temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }

        if (WINDOW_SIZE / 2 == i) {
            filteredValue = values[i];
        }
    }

    phone->Vertical[index] = filteredValue;
}