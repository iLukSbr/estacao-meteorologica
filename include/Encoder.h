/* Optical switch encoder speed sensor */

#pragma once

#ifndef _ENCODER
    #define _ENCODER
    #define _ENCODER_ 1
#endif

#include "Component.h"

#define ENCODER_PIN 2
#define ENCODER_N 36// Number of encoder interrupts
#define RADIUS_TO_CUP 0.000085// (km) Radius from bearing center to cup center
#define ENCODER_KEY "velocidadeVento"

class Encoder : public Component{
    private:
        volatile int pulses;

        float info;

        static Encoder* instance;// Declare the static member variable

        unsigned long timeold;

    public:
        Encoder();
        ~Encoder();

        float getSpeed() const;

        void makeJson(JsonDocument& doc) override;
        void counter();
        void print() const override;
        void read() override;
        void start() override;

        static void interruptHandler();
};