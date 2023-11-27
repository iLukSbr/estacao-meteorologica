#pragma once

#include "Component.h"
#include "GY511.h"

#ifndef _WIND_VANE
    #define _WIND_VANE
    #define _WIND_VANE_ 1
#endif

#define RS_PIN1 33
#define RS_PIN2 35
#define RS_PIN3 37
#define RS_PIN4 39
#define RS_PIN5 41
#define RS_PIN6 43
#define RS_PIN7 45
#define RS_PIN8 47
#define RS_PIN9 23
#define RS_PIN10 25
#define RS_PIN11 27
#define RS_PIN12 29
#define RS_PIN13 31
#define RS_PIN14 48
#define RS_PIN15 46
#define RS_PIN16 38
#define WINDVANE_KEY "direcaoVento"

class WindVane : public Component{
    private:
        GY511* magnetometer;
        
        char info[4] = {0};

        float heading;
        float fixed_heading;

        const char directions[16][3] = {
            {' ', ' ', 'N'},
            {'N', 'N', 'E'},
            {' ', 'N', 'E'},
            {'E', 'N', 'E'},
            {' ', ' ', 'E'},
            {'E', 'S', 'E'},
            {' ', 'S', 'E'},
            {'S', 'S', 'E'},
            {' ', ' ', 'S'},
            {'S', 'S', 'W'},
            {' ', 'S', 'W'},
            {'W', 'S', 'W'},
            {' ', ' ', 'W'},
            {'W', 'N', 'W'},
            {' ', 'N', 'W'},
            {'N', 'N', 'W'},
	    };

    public:
        WindVane();
        ~WindVane();

        const char* getDirection() const;

        void makeJson(JsonDocument& doc) override;
        void print() const override;
        void read() override;
        void start() override;
};