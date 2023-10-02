/* TEMT6000 precision luminosity sensor */

#pragma once

#include "Component.h"

#define TEMT6000_PIN A0

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