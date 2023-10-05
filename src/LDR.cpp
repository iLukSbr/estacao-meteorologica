/* LDR luminosity sensor */

#include "LDR.h"

LDR::LDR(byte _ldr_pin, unsigned int _resistor = 10000):
    ldr_pin(_ldr_pin),
    info(0.f),
    resistor(_resistor)
{
    start();
}

LDR::~LDR(){

}

float LDR1::getIlluminance() const{
    return info;
}

void LDR1::print() const{
    Serial.println(F("LDR1:"));
    Serial.print(F("illuminance = "));
    Serial.print(info);
    Serial.println(F(" lux"));
}

void LDR1::read(){
    float resistor_voltage = analogRead(ldr_pin)*5.f/1024.f;
    float ldr_voltage = 5.f - resistor_voltage;
    float ldr_resistance = ldr_voltage*resistor/resistor_voltage;
    info = 12518931*pow(ldr_resistance, -1.405);
}

void LDR1::start(){
    pinMode(ldr_pin, INPUT);
    started = true;
}