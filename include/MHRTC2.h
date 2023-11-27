/* MH-Real Time Clock 2  DS1302*/

#pragma once

#include <ThreeWire.h>
#include <RtcDS1302.h>

#include "Component.h"

#ifndef _MHRTC2
    #define _MHRTC2
#endif

#define RTC_CLK_PIN 40// Serial Clock
#define RTC_DAT_PIN 42// Input/Output
#define RTC_RST_PIN 44// Chip Enable

class MHRTC2 : public Component{
    private: 
        ThreeWire* myWire;

        RtcDS1302<ThreeWire>* rtc;

        char info[26] = {0};

    public:
        MHRTC2();
        ~MHRTC2();

        const char* getDateTime() const;
        void makeDateTime(const RtcDateTime& dt);

        void print() const override;
        void read() override;
        void start() override;
};