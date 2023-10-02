/* LDR luminosity sensor */

#include "LDR1.h"

LDR1::LDR1():
    info(0.f)
{
    start();
}

LDR1::~LDR1(){

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
    float resistor_voltage = analogRead(LDR1_PIN)*5.f/1024.f;
    float ldr_voltage = 5.f - resistor_voltage;
    float ldr_resistance = ldr_voltage*LDR1_RESISTOR/resistor_voltage;
    info = 12518931*pow(ldr_resistance, -1.405);
}

void LDR1::start(){
    pinMode(LDR1_PIN, INPUT);
    started = true;
}