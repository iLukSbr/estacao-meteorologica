/* Component */

#pragma once

#define START_TRIES 3// Attempts to start sensor
#define LOOP_DELAY 100// (ms) Delay between start attempts

class Component{
    protected:
        bool started;

        unsigned long measure_delay;
        unsigned long stopwatch;
    
    public:
        Component();
        virtual ~Component();

        bool isStarted() const;
        bool verifyDelay();

        virtual void makeJson(JsonDocument& doc);
        virtual void print() const = 0;
        virtual void read() = 0;
        virtual void start() = 0;
};