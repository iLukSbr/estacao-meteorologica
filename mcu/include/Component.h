#pragma once

#include <Arduino.h>

#define START_TRIES 3// Attempts to start sensor
#define LOOP_DELAY 100// (ms) Delay between start attempts

class Component{
    protected:
        bool started;
    
    public:
        Component();
        virtual ~Component();

        virtual bool isStarted() const = 0;

        virtual void print() const = 0;
        virtual void read() = 0;
        virtual void start() = 0;      
};