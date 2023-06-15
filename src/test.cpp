// #include <Arduino.h>
// #include "ads1256/adc.hpp"
// #include "ads1256/channel.hpp"
// #include "ads1256/gain.hpp"
// #include "ads1256/sample.hpp"
// #include "config.hpp"

// #define DIFFERENTIAL 0

// ADS1256 adc(SS, PA3, PA2);

// void setup() {
//     Serial.begin(SERIAL_BAUD);
//     adc.begin();

//     adc.setBuffer(true);
//     adc.setGain(GAIN_AMP_1X);
//     adc.setSample(SAMPLE_RATE_2000);
// }

// void loop() {
// #if DIFFERENTIAL
//     for (uint8_t i = 1; i <= 4; i++) {
//         int32_t raw;
//         switch (i) {
//             case 1:
//                 raw = adc.getDifferential(INPUT_AIN1, INPUT_AIN2);
//                 break;
//             case 2:
//                 raw = adc.getDifferential(INPUT_AIN3, INPUT_AIN4);
//                 break;
//             case 3:
//                 raw = adc.getDifferential(INPUT_AIN5, INPUT_AIN6);
//                 break;
//             case 4:
//                 raw = adc.getDifferential(INPUT_AIN7, INPUT_AIN8);
//                 break;
//         }

//         double voltage = adc.getVoltage(raw);
//         Serial.print("CH");
//         Serial.print(i);
//         Serial.print(": ");
//         Serial.print(voltage, 10);
//         Serial.print("\t");
//     }
// #else
//     for (uint8_t i = 1; i <= 8; i++) {
//         int32_t raw;
//         switch (i) {
//             case 1:
//                 raw = adc.getDifferential(INPUT_AIN1, INPUT_AINCOM);
//                 break;
//             case 2:
//                 raw = adc.getDifferential(INPUT_AIN2, INPUT_AINCOM);
//                 break;
//             case 3:
//                 raw = adc.getDifferential(INPUT_AIN3, INPUT_AINCOM);
//                 break;
//             case 4:
//                 raw = adc.getDifferential(INPUT_AIN4, INPUT_AINCOM);
//                 break;
//             case 5:
//                 raw = adc.getDifferential(INPUT_AIN5, INPUT_AINCOM);
//                 break;
//             case 6:
//                 raw = adc.getDifferential(INPUT_AIN6, INPUT_AINCOM);
//                 break;
//             case 7:
//                 raw = adc.getDifferential(INPUT_AIN7, INPUT_AINCOM);
//                 break;
//             case 8:
//                 raw = adc.getDifferential(INPUT_AIN8, INPUT_AINCOM);
//                 break;
//         }

//         double voltage = adc.getVoltage(raw);
//         Serial.print("CH");
//         Serial.print(i);
//         Serial.print(": ");
//         Serial.print(voltage, 10);
//         Serial.print("\t");
//     }
// #endif

//     Serial.println();
// }
