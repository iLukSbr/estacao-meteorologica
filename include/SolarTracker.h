/* Solar Tracker */

#pragma once

#ifndef _SOLAR_TRACKER
    #define _SOLAR_TRACKER
    #define _SOLAR_TRACKER_ 1
#endif

#include "Component.h"
#include "I2CServoDriver.h"
#include "ITGMPU6050.h"
#include "LDR.h"

#define TOLERANCE 10
#define SERVO_BASE_PIN 14
#define SERVO_PANEL_PIN 15
#define LDR1_PIN A1
#define LDR2_PIN A2
#define LDR3_PIN A3
#define LDR4_PIN A4
#define PWM_MIN 99
#define PWM_MAX 456
#define LDR1_RESISTOR 6650
#define LDR2_RESISTOR 7120
#define LDR3_RESISTOR 8070
#define LDR4_RESISTOR 6430

class SolarTracker : public Component{
    private:
        bool light_change_detected;

        I2CServoDriver* servo_base;
        I2CServoDriver* servo_panel;

        ITGMPU6050* gyro;

        LDR* ldr1;
        LDR* ldr2;
        LDR* ldr3;
        LDR* ldr4;

    public:
        SolarTracker();
        ~SolarTracker();

        void checkLightChange();
        void checkServosMovement();
        void flip();
        void lightChangeDetected();
        void print() const;
        void read();
        void start();
        void unblockServos();
};