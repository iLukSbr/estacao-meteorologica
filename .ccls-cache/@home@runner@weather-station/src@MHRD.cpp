/* Rain sensor */

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

void MHRD::print() const{
    Serial.println(F("Rain sensor MHRD:"));
    Serial.print(F("raining = "));
    Serial.println(info ? F("true") : F("false"));
}
void MHRD::read(){
    if(digitalRead(MHRD_PIN) == HIGH)
        info = false;
    else
        info = true;
}

void MHRD::start(){
    pinMode(MHRD_PIN, INPUT);
    started = true;
}