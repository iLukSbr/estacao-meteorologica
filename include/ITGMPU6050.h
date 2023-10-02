/* ITGMPU6050 gyroscope, accelerometer and thermometer */

#pragma once

#include <Wire.h>
#include <MPU6050_tockn.h>

#include "Component.h"

class ITGMPU6050 : public Component{
    private:
        MPU6050* mpu6050;

       double info[3] = {0.f};

    public:
        ITGMPU6050();
        ~ITGMPU6050();

        float getAngleX() const;
        float getAngleY() const;
        float getAngleZ() const;
        // float getTemperatureCelsius() const;
        // float getTemperatureKelvin() const;

        void print() const override;
        void read() override;
        void start() override;
};