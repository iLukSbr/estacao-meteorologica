/* Relay module */

#pragma once

#ifndef _RELAY
    #define _RELAY
    #define _RELAY_ 1
#endif

#include "Component.h"

#define RELAY_PIN 4

class Relay : public Component
{
    private:
        bool info;

    public:
        Relay();
        ~Relay();

        bool getState() const;

        void off();
        void on();
        void print() const;
        void read();
        void start();
};