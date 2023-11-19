/* 16 channel demultimplexer CD74HC4067 */

#pragma once

#ifndef _CD74HC4067
    #define _CD74HC4067
    #define _CD74HC4067_ 1
#endif

#include <Mux.h>

#include "Component.h"
#include "GY511.h"

#define CD74HC4067_SIGNAL_PIN 12
#define CD74HC4067_CHANNEL_PINS Pinset(8, 9, 10, 11)

using namespace admux;

class CD74HC4067 : public GY511{
    private:
        GY511* magnetometer;

        Mux* mux;

        char info[3] = {0};

    public:
        CD74HC4067();
        ~CD74HC4067();

        const char* getDirection() const;

        void print() const override;
        void read() override;
        void start() override;
};