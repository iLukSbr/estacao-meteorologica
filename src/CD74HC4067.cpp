/* 16 channel demultimplexer CD74HC4067 */

#include "CD74HC4067.h"

CD74HC4067::CD74HC4067():
    magnetometer(new GY511()),
    mux(new Mux(Pin(CD74HC4067_SIGNAL_PIN, INPUT, PinType::Digital), CD74HC4067_CHANNEL_PINS))
{
    start();
}

CD74HC4067::~CD74HC4067(){
    delete magnetometer;
    delete mux;
}

const char* CD74HC4067::getDirection() const{
    return info;
}

void CD74HC4067::print() const{
    Serial.println(F("CD74HC4067:"));
    Serial.print(F("direction = "));
    Serial.println(getDirection());
}

void CD74HC4067::read(){
    byte part;
    const char** directions = magnetometer->getDirectionsArray();
    magnetometer->read();
    for(byte i=0; i<mux->channelCount(); i++){
        if((mux->read(i) == HIGH) ? true : false){
            part = magnetometer->getDirectionPart()+i;
            info[0] = directions[part][0];
            info[1] = directions[part][1];
            info[2] = directions[part][2];
            info[3] = '\n';
            break;
        }
    }
}

void CD74HC4067::start(){
    started = true;
}