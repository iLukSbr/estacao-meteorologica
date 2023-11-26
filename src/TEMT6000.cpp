/* TEMT6000 precision luminosity sensor */

#include "pch.h"
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

void TEMT6000::makeJson(JsonDocument& doc){
    doc[F(ILLUMINANCE_KEY)] = getIlluminance();
}

void TEMT6000::print() const{
    Serial.println(F("TEMT6000 luxmeter:"));
    Serial.print(F("illuminance = "));
    Serial.print(info);
    Serial.println(F(" lux"));
}

void TEMT6000::read(){
    float median = 0.f;
    Serial.println(F("Reading TEMT6000 luxmeter..."));
    for(byte i=0; i<TEMT6000_MEASURES; i++){
        median += analogRead(TEMT6000_PIN)/1.024;
        delay(10);
    }
    info = median*TEMT6000_OFFSET/TEMT6000_MEASURES;
}

void TEMT6000::start(){
    Serial.println(F("Starting TEMT6000 luxmeter..."));
    pinMode(TEMT6000_PIN, INPUT);
    started = true;
    Serial.println(F("TEMT6000 luxmeter OK!"));
}