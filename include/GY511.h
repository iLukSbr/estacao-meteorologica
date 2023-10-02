/* GY511 magnetometer compass and accelerometer */

#pragma once

#include <Wire.h>
#include <LSM303.h>

#include "Component.h"

#define GY511_CALIBRATION_DURATION 10000// (ms) Time needed to calibrate

class GY511 : public Component{
    private:
        LSM303* compass;

        char info[4] = {0};
        
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
        GY511();
        ~GY511();
        
        const char* getDirection() const;

        void print() const override;
        void read() override;
        void start() override;
};