#include "gnss.hpp"

GNSS::GNSS(uint8_t rxPin, uint8_t txPin, uint16_t baudRate) {
    this->Serial = new SoftwareSerial(rxPin, txPin);
}

void GNSS::begin() {
    this->Serial->begin(this->baud);
}

void GNSS::getCoordination(Geophone* geophone) {
    while (this->Serial->available()) {
        char c = this->Serial->read();
        if (c == '$') {
            char sentence[80];
            int i = 0;
            do {
                c = this->Serial->read();
                sentence[i++] = c;
            } while (c != '\r' && i < 80);

            if (strncmp(sentence, "GPGGA", 5) == 0) {
                char* token = strtok(sentence, ",");
                int j = 0;
                while (token != NULL) {
                    if (j == 2) {
                        float lat = atof(token);
                        geophone->Latitude = lat;
                    }
                    if (j == 4) {
                        float lon = atof(token);
                        geophone->Longitude = lon;
                    }
                    if (j == 9) {
                        float alt = atof(token);
                        geophone->Altitude = alt;
                    }
                    token = strtok(NULL, ",");
                    j++;
                }
            }
        }
    }
}