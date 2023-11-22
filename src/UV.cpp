/* Taidacent UV sensor */

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

void UV::print() const{
    Serial.println(F("Taidacent UV:"));
    Serial.print(F("UV index = "));
    Serial.println(info);
}

void UV::read(){
    unsigned short sum = 0;
    // for(byte i=0; i<UV_MEASURES; i++){
        sum += constrain(map(analogRead(UV_PIN), 0, 203, 0, 10), 0, 11);// Converts sensor reading to UV index
        // Serial.println("Lendo uv");
    // }
    info = sum;
    // info = sum/UV_MEASURES;
}

void UV::start(){
    pinMode(UV_PIN, INPUT);
    started = true;
}