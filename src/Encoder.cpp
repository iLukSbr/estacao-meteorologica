/* Optical switch encoder speed sensor */
//TODO: attachInterrupt(0, counter, FALLING);

#include "pch.h"
#include "Encoder.h"

Encoder::Encoder():
    pulses(0),
    info(0.f),
    timeold(0)
{
    Serial.println(F("Starting Encoder Optocoupler wind speed sensor..."));
    start();
    Serial.println(F("Encoder Optocoupler wind speed sensor OK!"));
}

Encoder::~Encoder(){
    
}

float Encoder::getSpeed() const{
    return info;
}

void Encoder::interruptHandler(){// Call the non-static member function 'counter()' via the instance pointer
    instance->counter();
}

void Encoder::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F("velocidadeVento")] = getSpeed();
}

void Encoder::print() const{
    Serial.println(F("Encoder: "));
    Serial.print(F("speed = "));
    Serial.print(getSpeed());
    Serial.println(F(" km/h"));
}

void Encoder::read(){
    Serial.println(F("Reading Encoder Optocoupler wind speed sensor..."));
    detachInterrupt(digitalPinToInterrupt(ENCODER_PIN));
    if(pulses <= 3)
        pulses = 0;
    info = RADIUS_TO_CUP*360000*pulses*PI/(millis() - timeold);
    timeold = millis();
    pulses = 0;
    start();
}

void Encoder::start(){
    pinMode(ENCODER_PIN, INPUT);
    instance = this;// Set the instance pointer to 'this' for later use in the interrupt handler
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), &Encoder::interruptHandler, FALLING);
    started = true;
}

void Encoder::counter(){
  pulses++;
}

Encoder* Encoder::instance = nullptr;// Initialize the static member variable