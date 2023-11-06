/* GPS uBlox */

#pragma once

#ifndef _GYNEO6MV2
    #define _GYNEO6MV2
    #define _GYNEO6MV2_ 1
#endif

#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#include "Component.h"

#define GPS_RX_PIN 7
#define GPS_TX_PIN 6
#define GPS_SERIAL_BAUD 9600

class GYNEO6MV2 : public Component{
    private:
        TinyGPSPlus gps;

        char date_time[32] = {0};

        float info[2] = {0.f};

    public:
        GYNEO6MV2();
        ~GYNEO6MV2();

        const char* getDateTime() const;

        float getLatitude() const;
        float getLongitude() const;

        void print() const override;
        void read() override;
        void start() override;
};