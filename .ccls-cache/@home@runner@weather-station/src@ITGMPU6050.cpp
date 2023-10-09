/* ITGMPU6050 gyroscope, accelerometer and thermometer */

#include "ITGMPU6050.h"

ITGMPU6050::ITGMPU6050():
    mpu6050(new MPU6050(Wire))
{
    start();
}

ITGMPU6050::~ITGMPU6050(){
    delete mpu6050;
}

float ITGMPU6050::getAngleX() const{
    return info[0];
}

float ITGMPU6050::getAngleY() const{
    return info[1];
}

float ITGMPU6050::getAngleZ() const{
    return info[2];
}

// float ITGMPU6050::getTemperatureCelsius() const{
//     return info[3];
// }

// float ITGMPU6050::getTemperatureKelvin() const{
//     return info[3] + 273.15;
// }

void ITGMPU6050::print() const{
    Serial.println(F("ITGMPU6050:"));
    Serial.print("angle X = ");
    Serial.print(getAngleX());
    Serial.println(F("°"));
    Serial.print("angle Y = ");
    Serial.print(getAngleY());
    Serial.println(F("°"));
    Serial.print("angle Z = ");
    Serial.print(getAngleZ());
    Serial.println(F("°"));
    // Serial.print("temperature = ");
    // Serial.print(getTemperatureCelsius());
    // Serial.print(F(" °C = "));
    // Serial.print(getTemperatureKelvin());
    // Serial.println(F(" K"));
}

void ITGMPU6050::read(){
    mpu6050->update();
    info[0] = mpu6050->getAngleX();
    info[1] = mpu6050->getAngleY();
    info[2] = mpu6050->getAngleZ();
    // info[3] = mpu6050->getTemp();
}

void ITGMPU6050::start(){
    Wire.begin();
    mpu6050->begin();
    mpu6050->calcGyroOffsets(true);
    started = true;
}