// #include <Arduino.h>
// #include "ads1256/adc.hpp"
// #include "ads1256/channel.hpp"
// #include "ads1256/gain.hpp"
// #include "ads1256/sample.hpp"

// ADS1256 adc(SS, PA3, PA2);

// void setup() {
//     Serial.begin(115200);
//     adc.begin();

//     adc.setGain(GAIN_AMP_1X);
//     adc.setSample(SAMPLE_RATE_30000);
// }

// void loop() {
//     for (uint8_t i = 1; i <= 8; i++) {
//         int32_t raw;
//         switch (i) {
//             case 1:
//                 raw = adc.getDifferential(POSITIVE_AIN1, NEGATIVE_AINCOM);
//                 break;
//             case 2:
//                 raw = adc.getDifferential(POSITIVE_AIN2, NEGATIVE_AINCOM);
//                 break;
//             case 3:
//                 raw = adc.getDifferential(POSITIVE_AIN3, NEGATIVE_AINCOM);
//                 break;
//             case 4:
//                 raw = adc.getDifferential(POSITIVE_AIN4, NEGATIVE_AINCOM);
//                 break;
//             case 5:
//                 raw = adc.getDifferential(POSITIVE_AIN5, NEGATIVE_AINCOM);
//                 break;
//             case 6:
//                 raw = adc.getDifferential(POSITIVE_AIN6, NEGATIVE_AINCOM);
//                 break;
//             case 7:
//                 raw = adc.getDifferential(POSITIVE_AIN7, NEGATIVE_AINCOM);
//                 break;
//             case 8:
//                 raw = adc.getDifferential(POSITIVE_AIN8, NEGATIVE_AINCOM);
//                 break;
//             default:
//                 break;
//         }

//         double voltage = adc.getVoltage(raw);
//         Serial.print("CH");
//         Serial.print(i);
//         Serial.print(": ");
//         Serial.print(voltage, 10);
//         Serial.print("\t");
//     }

//     Serial.println();
// }
