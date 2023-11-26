/* ITGMPU6050 gyroscope, accelerometer and thermometer */

#include "pch.h"
#include "ITGMPU6050.h"

ITGMPU6050::ITGMPU6050():
    moving(false),
    rate_roll(0.f),
    rate_pitch(0.f),
    rate_yaw(0.f),
    rate_cali_roll(0.f),
    rate_cali_pitch(0.f),
    rate_cali_yaw(0.f),
    rate_cali_number(0)
{
    start();
}

ITGMPU6050::~ITGMPU6050(){

}

bool ITGMPU6050::isMoving() const{
    return moving;
}

float ITGMPU6050::getRollRate() const{
    return info[0];
}

float ITGMPU6050::getPitchRate() const{
    return info[1];
}

float ITGMPU6050::getYawRate() const{
    return info[2];
}

void ITGMPU6050::calibrate(){
    for(rate_cali_number=0; rate_cali_number<MPU6050_MAX; rate_cali_number++){
        gyroSignals();
        rate_cali_roll += rate_roll;
        rate_cali_pitch += rate_pitch;
        rate_cali_yaw += rate_yaw;
        delay(1);
    }
    rate_cali_roll /= MPU6050_MAX;
    rate_cali_pitch /= MPU6050_MAX;
    rate_cali_yaw /= MPU6050_MAX;
    gyroSignals();
    rate_roll -= rate_cali_roll;
    rate_pitch -= rate_cali_pitch;
    rate_yaw -= rate_cali_yaw;
}

void ITGMPU6050::gyroSignals(){
    // Low pass filter
    Wire.beginTransmission(0x68);// Gyroscope I²C communication start
    Wire.write(0x1A);// 0X1A = registry address
    Wire.write(0x05);//10 Hz frequency cut
    Wire.endTransmission();

    // Define sensitivity factor of scale
    Wire.beginTransmission(0x68);// Gyroscope I²C communication start 
    Wire.write(0x1B);// 1B = registry entry for scale change
    Wire.write(0x8);// 65.5 LSB/°/S
    Wire.endTransmission();

    // Access gyroscope measures
    Wire.beginTransmission(0x68);// Gyroscope I²C communication start          
    Wire.write(0x43);// First registry entry
    Wire.endTransmission();

    Wire.requestFrom(0x68, 6);

    int16_t gyro_x = Wire.read()<<8 | Wire.read();// Read the gyro measures around the X axis
    int16_t gyro_y = Wire.read()<<8 | Wire.read();// Read the gyro measures around the Y axis
    int16_t gyro_z = Wire.read()<<8 | Wire.read();// Read the gyro measures around the Z axis

    rate_roll = (float)gyro_x/65.5;
    rate_pitch = (float)gyro_y/65.5;
    rate_yaw = (float)gyro_z/65.5;
}

void ITGMPU6050::print() const{
    Serial.println(F("ITGMPU6050:"));
    Serial.print(F("roll rate = "));
    Serial.print(info[0]);
    Serial.println(F(" °/s"));
    Serial.print(F("pitch rate = "));
    Serial.print(info[1]);
    Serial.println(F(" °/s"));
    Serial.print(F("yaw rate = "));
    Serial.print(info[2]);
    Serial.println(F(" °/s"));
}

void ITGMPU6050::read(){
    gyroSignals();
    rate_roll -= rate_cali_roll;
    rate_pitch -= rate_cali_pitch;
    rate_yaw -= rate_cali_yaw;
    if(abs(rate_roll) > SENSIBILITY || abs(rate_pitch) > SENSIBILITY || abs(rate_yaw) > SENSIBILITY)
        moving = true;
    else
        moving = false;
    info[0] = rate_roll;
    info[1] = rate_pitch;
    info[2] = rate_yaw;
}

void ITGMPU6050::start(){
    Serial.println(F("Starting ITG/MPU6050..."));
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);// Puts gyroscope into power on mode
    Wire.write(0x00);
    Wire.endTransmission();
    calibrate();
    started = true;
}