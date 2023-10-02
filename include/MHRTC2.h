/* MH-Real Time Clock 2  DS1302*/

#pragma once

#include <RTClib.h>

#include "Component.h"

#define RTC_CLK_PIN 2// Serial Clock
#define RTC_DAT_PIN 3// Input/Output
#define RTC_RST_PIN 4// Chip Enable

class MHRTC2 : public Component{
    private: 
        DS1302* rtc;

        char info[20] = {0};

    public:
        MHRTC2();
        ~MHRTC2();

        char* getDateTime() const;

        void print() const override;
        void read() override;
        void start() override;
};