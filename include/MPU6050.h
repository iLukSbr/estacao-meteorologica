/* MPU6050 gyroscope, accelerometer and thermometer */

#pragma once

#include <Wire.h>
#include <MPU6050_tockn.h>

#include "Component.h"

class MPU6050{
    private:
        MPU6050 *mpu6050;

        float info[4] = {0.f};

    public:
        MPU6050();
        ~MPU6050();

        float getAngleX() const;
        float getAngleY() const;
        float getAngleZ() const;
        float getTemperatureCelsius() const;
        float getTemperatureKelvin() const;

        void print() const override;
        void read() override;
        void start() override;
}