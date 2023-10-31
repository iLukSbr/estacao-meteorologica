/* Relay module */

#include "Relay.h"

Relay::Relay():
    info(true)
{
    start();
    read();
}

Relay::~Relay(){
    
}

bool Relay::getState() const{
    return info;
}

void Relay::print() const{
    Serial.print(F("Relay: "));
    Serial.println(info ? F("on") : F("off"));
}

void Relay::read(){
    if(info)
        digitalWrite(RELAY_PIN, HIGH);
    else
        digitalWrite(RELAY_PIN, LOW);
}

void Relay::setState(bool state){
    if(state)
        info = true;
    else
        info = false;
}

void Relay::start(){
    pinMode(RELAY_PIN, OUTPUT);
    started = true;
}