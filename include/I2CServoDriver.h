/* Servo motors */

#pragma once

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "Component.h"

#define POTENTIOMETER_PIN A3
#define SERVO_FREQ 50.f // Analog servos run at ~50 Hz updates
#define OSCILLATOR_FREQ 27000000

class I2CServoDriver : public Component{
    private:
        static Adafruit_PWMServoDriver* pwm;

        byte count;
        byte pin;

        unsigned short info = 0;
        unsigned short min_freq;
        unsigned short max_freq;
        unsigned short step;

    public:
        I2CServoDriver(byte _pin, unsigned short _min_freq, unsigned short _max_freq, byte _count, unsigned short _step);
        ~I2CServoDriver();

        bool decreasePWM();
        bool increasePWM();

        unsigned short getServoPWM() const;

        void flip();
        void print() const;
        void read();
        void start();
};