/* Solar Tracker */

#pragma once

#ifndef _SOLAR_TRACKER
    #define _SOLAR_TRACKER
    #define _SOLAR_TRACKER_ 1
#endif

#include "Component.h"
#include "ServoMotor.h"
#include "ITGMPU6050.h"
#include "LDR.h"

#define TOLERANCE 20

#define SERVO_BASE_PIN 5
#define SERVO_BASE_STEP 1
#define SERVO_BASE_MIN 0
#define SERVO_BASE_MAX 180

#define SERVO_PANEL_PIN 6
#define SERVO_PANEL_STEP 20
#define SERVO_PANEL_MIN 20
#define SERVO_PANEL_MAX 160

#define LDR1_PIN A0
#define LDR1_RESISTOR 9970

#define LDR2_PIN A1
#define LDR2_RESISTOR 9970

#define LDR3_PIN A2
#define LDR3_RESISTOR 9970

#define LDR4_PIN A3
#define LDR4_RESISTOR 9970

class SolarTracker : public Component{
    private:
        bool light_change_detected;

        ServoMotor* servo_base;
        ServoMotor* servo_panel;

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
};