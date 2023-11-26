/* TEMT6000 precision luminosity sensor */

#pragma once

#ifndef _TEMT6000
    #define _TEMT6000
    #define _TEMT6000_ 1
#endif

#include "Component.h"

#define TEMT6000_PIN A5
#define TEMT6000_MEASURES 255
#define TEMT6000_OFFSET 5.5// multiplier
#define ILLUMINANCE_KEY "intensidadeLuminosa"

class TEMT6000 : public Component{
    private: 
        float info;

    public:
        TEMT6000();
        ~TEMT6000();

        float getIlluminance() const;

        void makeJson(JsonDocument& doc) override;
        void print() const override;
        void read() override;
        void start() override;
};