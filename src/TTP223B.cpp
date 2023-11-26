/* Touch module for LED light */

#include "pch.h"
#include "TTP223B.h"

TTP223B::TTP223B():
    info(false)
{
    start();
}

TTP223B::~TTP223B(){
    
}

volatile bool TTP223B::getLedState() const{
    return info;
}

void TTP223B::print() const{
    Serial.println(F("Touch sensor TTP223B:"));
    Serial.print(F("led = "));
    Serial.println(info ? F("on") : F("off"));
}

void TTP223B::read(){
    if(digitalRead(TTP223B_PIN))
        info = !info;
    if(info)
        digitalWrite(LED_PIN, HIGH);
    else
        digitalWrite(LED_PIN, LOW);
}

void TTP223B::interruptHandler(){// Call the non-static member function 'read()' via the instance pointer
    instance->read();
}

void TTP223B::start(){
    Serial.println("Starting TTP223B touch sensor...");
    pinMode(TTP223B_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);   
    instance = this;// Set the instance pointer to 'this' for later use in the interrupt handler
    attachInterrupt(digitalPinToInterrupt(TTP223B_PIN), &TTP223B::interruptHandler, CHANGE);
    started = true;
    Serial.println("TTP223B touch sensor OK!");
}

TTP223B* TTP223B::instance = nullptr;// Initialize the static member variable