/* Optical switch encoder speed sensor */

#include "Encoder.h"

Encoder::Encoder():
    info(0.f),
    measure_done(false),
    T1(0),
    T2(0),
    T(0)
{
    start();
}

Encoder::~Encoder(){
    
}

float Encoder::getSpeed(){
    return info;
}

void Encoder::INT0_ISR(){
    if(measure_done){
        T2 = micros();
        T = T2 - T1;
        measure_done = false;
    }
    else{
        T1 = micros();
        measure_done = true;
    }
}

void Encoder::print() const{
    Serial.println(F("Encoder: "));
    Serial.print(F("speed = "));
    Serial.print(getSpeed());
    Serial.println(F(" m/s"));
}

void Encoder::read(){
    float rpm = 60000000/(T*ENCODER_N);
    info = rpm*PI*CIRCUNFERENCE_DIAMETER/216.f;
}

void Encoder::start(){
    pinMode(ENCODER_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), INT0_ISR, RISING);
    started = true;
}