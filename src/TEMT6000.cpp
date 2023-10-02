/* TEMT6000 precision luminosity sensor */

#include "TEMT6000.h"

TEMT6000::TEMT6000():
    info(0)
{
    start();
}

TEMT6000::~TEMT6000(){

}

float TEMT6000::getIlluminance() const{
    return info;
}

void TEMT6000::print() const{
    Serial.println(F("TEMT6000:"));
    Serial.print(F("illuminance = "));
    Serial.print(info);
    Serial.println(F(" lux"));
}

void TEMT6000::read(){
    float volts = analogRead(TEMT6000_PIN)*5.f/1024.f;
    float amps = volts/10000.f;  // across 10,000 Ohms
    float microamps = amps*1000000.f;
    info = microamps*2.f;
}

void TEMT6000::start(){
    pinMode(TEMT6000_PIN, INPUT);
    started = true;
}