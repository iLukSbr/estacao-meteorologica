/* LDR luminosity sensor */

#include "LDR.h"

LDR::LDR(byte _ldr_pin, byte _count, unsigned int _resistor):
    ldr_pin(_ldr_pin),
    count(_count),
    info(0.f),
    resistor(_resistor)
{
    start();
}

LDR::~LDR(){

}

float LDR::getIlluminance() const{
    return info;
}

void LDR::print() const{
    Serial.print(F("LDR"));
    Serial.print(count);
    Serial.println(F(":"));
    Serial.print(F("illuminance = "));
    Serial.print(info);
    Serial.println(F(" lux"));
}

void LDR::read(){
    float median = 0.f, resistor_voltage, ldr_voltage, ldr_resistance;
    for(byte i=0; i<LDR_MEASURES; i++){
        resistor_voltage = analogRead(ldr_pin)*5.f/1024.f;
        ldr_voltage = 5.f - resistor_voltage;
        ldr_resistance = ldr_voltage*resistor/resistor_voltage;
        median += 12518931*pow(ldr_resistance, -1.405);
    }
    info = median/LDR_MEASURES;
}

void LDR::start(){
    Serial.print(F("Starting LDR"));
    Serial.print(count);
    Serial.println(F("..."));
    pinMode(ldr_pin, INPUT);
    started = true;
}