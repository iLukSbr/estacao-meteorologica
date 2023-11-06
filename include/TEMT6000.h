/* TEMT6000 precision luminosity sensor */

#pragma once

#ifndef _TEMT6000
    #define _TEMT6000
    #define _TEMT6000_ 1
#endif

#include "Component.h"

#define TEMT6000_PIN A0
#define TEMT6000_MEASURES 256

class TEMT6000 : public Component{
    private: 
        float info;

    public:
        TEMT6000();
        ~TEMT6000();

        float getIlluminance() const;

        void print() const override;
        void read() override;
        void start() override;
};