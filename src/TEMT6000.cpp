/* TEMT6000 precision luminosity sensor */

#include "TEMT6000.h"

TEMT6000::TEMT6000():
    info(0.f)
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
    float median = 0.f, volts, amps, microamps;
    // for(byte i=0; i<TEMT6000_MEASURES; i++){
        volts = analogRead(TEMT6000_PIN)*5.f/1024.f;
        amps = volts/10000.f;// across 10,000 Ohms
        microamps = amps*1000000.f;
        median += microamps*2.f;
    // }
    info = median;
    // info = median/TEMT6000_MEASURES;
}

void TEMT6000::start(){
    pinMode(TEMT6000_PIN, INPUT);
    started = true;
}