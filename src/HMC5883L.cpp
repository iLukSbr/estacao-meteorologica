/* HMC5883L magnetometer compass */

#include "HMC5883L.h"

HMC5883L::HMC5883L():
    compass(new QMC5883LCompass())// Instantiate compass
{// Create object
    start();
}

HMC5883L::~HMC5883L(){// Release memory
    delete compass;
}

const char* HMC5883L::getDirection() const{
    return info;
}

void HMC5883L::print() const{// Get data from component
    Serial.println(F("HMC5883L:"));
    Serial.print(F("direction = "));
    Serial.println(getDirection());
}

void HMC5883L::read(){
    compass->read();// Read magnetometer
    compass->getDirection(info, compass->getAzimuth());// Direction
    info[3] = '\0';
}

void HMC5883L::start(){
    compass->setADDR(HMC5883L_I2C_ADDRESS);
    compass->init();
    compass->setMode(HMC5883L_MODE, HMC5883L_ODR, HMC5883L_RNG, HMC5883L_OSR);
    compass->setSmoothing(HMC5883L_SMOOTHING_STEPS, HMC5883L_ADVANCED_SMOOTHING);
    started = true;
}