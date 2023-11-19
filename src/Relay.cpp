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

void Relay::off(){
    info = false;
    read();
}

void Relay::on(){
    info = true;
    read();
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

void Relay::start(){
    pinMode(RELAY_PIN, OUTPUT);
    started = true;
}