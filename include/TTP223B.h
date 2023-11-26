/* Touch module for LED light */

#pragma once

#ifndef _TTP223B
    #define _TTP223B
#endif

#include "Component.h"

#define TTP223B_PIN 19
#define LED_PIN 5

class TTP223B : public Component {
private:
    volatile bool info;
    
    static TTP223B* instance;// Declare the static member variable

public:
    TTP223B();
    ~TTP223B();

    volatile bool getLedState() const;

    void read() override;
    void start() override;
    void print() const override;

    static void interruptHandler();
};