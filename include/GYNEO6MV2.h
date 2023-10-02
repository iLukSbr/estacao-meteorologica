/* GPS uBlox */

#pragma once

#include <SoftwareSerial.h>
#include <TinyGPS.h>

#include "Component.h"

#define GPS_RX_PIN 7
#define GPS_TX_PIN 6
#define GPS_SERIAL_BAUD 9600

class GYNEO6MV2{
    private:
        TinyGPS* gps;

        SoftwareSerial* gpsSerial;

        float info[2] = {0.f};

    public:
        GYNEO6MV2();
        ~GYNEO6MV2();

        float getLatitude() const;
        float getLongitude() const;

        void print() const override;
        void read() override;
        void start() override;
};