/* Rain sensor */

#include "pch.h"
#include "MHRD.h"

MHRD::MHRD():
    info(false)
{
    start();
}

MHRD::~MHRD() {
    
}

bool MHRD::getRaining() const{
    return info;
}

void MHRD::makeJson(JsonDocument& doc){
    doc[F(RAINING_KEY)] = info;
}

void MHRD::print() const{
    Serial.println(F("MHRD rain sensor:"));
    Serial.print(F("raining = "));
    Serial.println(info ? F("true") : F("false"));
}
void MHRD::read(){
    Serial.println(F("Reading MHRD rain sensor..."));
    if(digitalRead(MHRD_PIN) == HIGH)
        info = false;
    else
        info = true;
}

void MHRD::start(){
    Serial.println(F("Starting MHRD rain sensor..."));
    pinMode(MHRD_PIN, INPUT);
    started = true;
    Serial.println(F("MHRD rain sensor OK!"));
}