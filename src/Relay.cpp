/* Relay module */

#include "pch.h"
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
    Serial.println(F("Reading relay..."));
    if(info)
        digitalWrite(RELAY_PIN, LOW);
    else
        digitalWrite(RELAY_PIN, HIGH);
}

void Relay::start(){
    Serial.println(F("Starting relay..."));
    pinMode(RELAY_PIN, OUTPUT);
    started = true;
    Serial.println(F("Relay OK!"));
}