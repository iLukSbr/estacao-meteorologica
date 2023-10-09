/* Servo motors */

#pragma once

#ifndef _I2CSERVODRIVER
    #define _I2CSERVODRIVER
    #define _I2CSERVODRIVER_ 1
#endif

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "Component.h"

#define POTENTIOMETER_PIN A3
#define SERVO_FREQ 50.f // Analog servos run at ~50 Hz updates
#define OSCILLATOR_FREQ 27000000

class I2CServoDriver : public Component{
    private:
        Adafruit_PWMServoDriver* pwm;

        byte pin;

        long info[2] = {0};

        unsigned short min_freq;
        unsigned short max_freq;

    public:
        I2CServoDriver(byte _pin, unsigned short _min_freq, unsigned short _max_freq, unsigned long _measure_delay);
        ~I2CServoDriver();

        bool moveLeft();
        bool moveRight();

        float getPotentiometerRead() const;

        long getServoPWM() const;

        void print() const;
        void read();
        void start();
};