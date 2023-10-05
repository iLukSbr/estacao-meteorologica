/* Magnetometer compass */

#pragma once

#ifndef _HMC5883L
    #define _HMC5883L
    #define _HMC5883L_ 1
#endif

#include <Wire.h>
#include <QMC5883LCompass.h>

#include "Component.h"

#define HMC5883L_I2C_ADDRESS 0x0D// I²C address
#define HMC5883L_SMOOTHING_STEPS 10// Smoothing steps
#define HMC5883L_ADVANCED_SMOOTHING true// Discard extreme values
#define HMC5883L_OSR 0x00// Over sample ratio 512
#define HMC5883L_RNG 0x10// Full scale 8G
#define HMC5883L_ODR 0x0C// Output data rate 200 Hz
#define HMC5883L_MODE 0x01// Continuous mode control

class HMC5883L : public Component{
    private:
        QMC5883LCompass* compass;
        char info[4] = {0};

    public:
        HMC5883L();
        ~HMC5883L();

        const char* getDirection() const;

        void print() const;
        void read();
        void start();
};