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
#define SERVO_SOLAR_PIN 15
#define SERVO_SOLAR_MIN  250 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_SOLAR_MAX  356 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_BASE_PIN 14
#define SERVO_BASE_MIN  250 // This is the 'minimum' pulse length count (out of 4096)
#define SERVO_BASE_MAX  356 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define OSCILLATOR_FREQ 27000000

class I2CServoDriver : public Component{
    private:
        Adafruit_PWMServoDriver pwm;

        long int info[2] = {0};

    public:
        I2CServoDriver();
        ~I2CServoDriver();

        float getPotentiometerRead() const;
        long getServoPWM() const;

        void print() const;
        void read();
        void start();
};