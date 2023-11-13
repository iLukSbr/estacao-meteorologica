/* Touch module for LED light */

#include "KY036.h"

KY036::KY036():
    info(false)
{
    start();
}

KY036::~KY036(){
    
}

void KY036::print() const{
    Serial.println(F("KY-036:"));
    Serial.print(F("led = "));
    Serial.println(info ? F("on") : F("off"));
}

void KY036::read(){
    if(digitalRead(KY036_PIN) == HIGH){
        info = !info;
        delay(500);
    }
    if(info)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);
}

void KY036::start(){
    pinMode(KY036_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    started = true;
}