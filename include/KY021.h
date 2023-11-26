/* KY-021 reed switch module for rain sensor tipping bucket */

#pragma once

#ifndef _KY021
    #define _KY021
    #define _KY021_ 1
#endif

#include "Component.h"
#include "MHRD.h"

#define KY021_PIN 3
#define SEESAW_VOLUME 0.002// liter
#define FUNNEL_AREA 0.01// m^2
#define KY021_KEY "volumeChuva"

class KY021 : public Component{
    private:
        volatile int pulses;

        float info;

        MHRD* rainmeter;

        static KY021* instance;// Declare the static member variable

        unsigned int timeold;

    public:
        KY021();
        ~KY021();
        
        float getRainfall() const;

        void counter();
        void makeJson(JsonDocument& doc) override;
        void print() const override;
        void read() override;
        void start() override;

        static void interruptHandler();
};