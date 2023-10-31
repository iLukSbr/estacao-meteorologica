/* Reed switch only */

#include "ReedSwitch.h"

ReedSwitch::ReedSwitch(byte _pin, byte _count):
    pin(_pin),
    count(_count)
{
    start();
}

ReedSwitch::~ReedSwitch(){

}

bool ReedSwitch::getState() const{
    return info;
}

void ReedSwitch::print() const{
    Serial.print(F("Reed switch "));
    Serial.print(count);
    Serial.println(F(":"))
    Serial.print(F("state = "));
    Serial.println(info ? F("on") : F("off"));
}

void ReedSwitch::read(){
    info = ((digitalRead(pin) == HIGH) ? true : false);
}

void ReedSwitch::start(){
    pinMode(pin, INPUT);
    started = true;
}