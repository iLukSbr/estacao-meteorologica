/* Touch module for LED light */

#pragma once

#ifndef _KY036
    #define _KY036
    #define _KY036_ 1
#endif

#include "Component.h"

#define KY036_PIN 26
#define LED_PIN 27

class KY036 : public Component{
    private:
        bool info;
    
    public:
        KY036();
        ~KY036();

        void read() override;
        void start() override;
        void print() const override;
};