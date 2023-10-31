/* Servo motor */

#pragma once

#ifndef _SERVO_MOTOR
    #define _SERVO_MOTOR
    #define _SERVO_MOTOR_ 1
#endif

#include <Servo.h>

#include "Component.h"

class ServoMotor : public Component{
    private:
        byte count;
        byte info;
        byte min_angle;
        byte max_angle;
        byte pin;
        byte step;

        Servo* servo;

    public:
        ServoMotor(byte _pin, byte _min_angle, byte _max_angle, byte _count, byte _step);
        ~ServoMotor();

        bool decreaseAngle();
        bool increaseAngle();

        byte getServoAngle() const;

        void flip();
        void print() const;
        void read();
        void start();
        void unblock();
};