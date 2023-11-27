/* MH-Real Time Clock 2  DS1302*/

#pragma once

#include <RTClib.h>

#include "Component.h"

#ifndef _MHRTC2
    #define _MHRTC2
#endif

#define RTC_CLK_PIN 40// Serial Clock
#define RTC_DAT_PIN 42// Input/Output
#define RTC_RST_PIN 44// Chip Enable

class MHRTC2 : public Component{
    private: 
        DS1302* rtc;

        char info[20] = {0};

    public:
        MHRTC2();
        ~MHRTC2();

        const char* getDateTime() const;

        void print() const override;
        void read() override;
        void start() override;
};