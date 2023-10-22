/* ITGMPU6050 gyroscope, accelerometer and thermometer */

#pragma once

#include <Wire.h>

#include "Component.h"

#define MPU6050_MAX 4000
#define SENSIBILITY 10

class ITGMPU6050 : public Component{
    private:
        bool moving;

        // Gyro variables
        float rate_roll, rate_pitch, rate_yaw;

        // Sensor calibration
        float rate_cali_roll, rate_cali_pitch, rate_cali_yaw;

        int rate_cali_number;

        float info[3] = {0.f};

    public:
        ITGMPU6050();
        ~ITGMPU6050();

        bool isMoving() const;

        float getAngleX() const;
        float getAngleY() const;
        float getAngleZ() const;
        // float getTemperatureCelsius() const;
        // float getTemperatureKelvin() const;

        void gyroSignals();
        void print() const override;
        void read() override;
        void start() override;
        void gyro_signals();
};
