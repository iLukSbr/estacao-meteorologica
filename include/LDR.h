/* LDR luminosity sensor */

#pragma once

#ifndef _LDR
    #define _LDR
    #define _LDR_ 1
#endif

#include "Component.h"

#define LDR_MEASURES 255

class LDR : public Component{
    private: 
        byte ldr_pin;
        byte count;

        float info;

        unsigned int resistor;

    public:
        LDR(byte _ldr_pin, byte _count = 0, unsigned int _resistor = 10000);
        ~LDR();

        float getIlluminance() const;

        void print() const override;
        void read() override;
        void start() override;
};