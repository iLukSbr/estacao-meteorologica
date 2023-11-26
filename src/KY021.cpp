/* KY-021 reed switch module for rain sensor tipping bucket */

#include "pch.h"
#include "KY021.h"

KY021::KY021():
    pulses(0),
    info(0.f),
    timeold(0)
{
    measure_delay = 10000;
    Serial.println(F("Starting KY-021 reed switch module..."));
    start();
    started = true;
    Serial.println(F("KY-021 reed switch module OK!"));
}

KY021::~KY021(){
    delete rainmeter;
}

float KY021::getRainfall() const{
    return info;
}

void KY021::counter(){
    pulses++;
}

void KY021::interruptHandler(){// Call the non-static member function 'counter()' via the instance pointer
    instance->counter();
}

void KY021::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F(KY021_KEY)] = serialized(String(getRainfall(),4));
}

void KY021::print() const{
    Serial.println(F("Pluviometer KY-021 reed switch module:"));
    Serial.print(F("rain volume = "));
    Serial.print(info, 4);
    Serial.println(F(" mm/h"));
}

void KY021::read(){
    Serial.println(F("Reading KY-021 reed switch module..."));
    detachInterrupt(digitalPinToInterrupt(KY021_PIN));
    info = (SEESAW_VOLUME*pulses/FUNNEL_AREA)*3600000.f/(millis() - timeold);
    Serial.print(F("pulses = "));
    Serial.println(pulses);
    pulses = 0;
    start();
}

void KY021::start(){
    pinMode(KY021_PIN, INPUT);
    instance = this;// Set the instance pointer to 'this' for later use in the interrupt handler
    attachInterrupt(digitalPinToInterrupt(KY021_PIN), &KY021::interruptHandler, FALLING);
    timeold = millis();
}

KY021* KY021::instance = nullptr;// Initialize the static member variable