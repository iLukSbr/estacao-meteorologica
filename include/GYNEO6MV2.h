/* GPS uBlox */

#pragma once

#ifndef GYNEO6MV2
    #define GYNEO6MV2
#endif

#include <SoftwareSerial.h>
#include <TinyGPS.h>

#include "Component.h"

#define GPS_RX_PIN 7
#define GPS_TX_PIN 6
#define GPS_SERIAL_BAUD 9600

class GYNEO6MV2 : public Component{
    private:
        TinyGPS gps;

        // char date_time[32] = {0};

        float info[2] = {0.f};

    public:
        GYNEO6MV2();
        ~GYNEO6MV2();

        // const char* getDateTime() const;

        float getLatitude() const;
        float getLongitude() const;

        void print() const override;
        void read() override;
        void start() override;
};