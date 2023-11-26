/* Taidacent UV sensor */

#include "pch.h"
#include "uv.h"

UV::UV():
    info(0)
{
    start();
}

UV::~UV(){

}

byte UV::getUVIndex() const{
    return info;
}

void UV::makeJson(JsonDocument& doc){
    doc[F(UV_INDEX_KEY)] = getUVIndex();
}

void UV::print() const{
    Serial.println(F("Taidacent UV sensor:"));
    Serial.print(F("UV index = "));
    Serial.println(info);
}

void UV::read(){
    unsigned short sum = 0;
    Serial.println(F("Reading Taidacent UV sensor..."));
    for(byte i=0; i<UV_MEASURES; i++)
        sum += constrain(map(analogRead(UV_PIN), 0, 203, 0, 10), 0, 11);// Converts sensor reading to UV index
    info = sum/UV_MEASURES;
}

void UV::start(){
    Serial.println(F("Starting Taidacent UV sensor..."));
    pinMode(UV_PIN, INPUT);
    started = true;
    Serial.println(F("Taidacent UV sensor OK!"));
}