// /* Optical switch encoder speed sensor */
// //TODO: attachInterrupt(0, counter, FALLING);

// #include "pch.h"
// #include "Encoder.h"

// Encoder::Encoder():
//     info(0.f),
//     timeold(0),
//     rpm(0)
// {
//     start();
// }

// Encoder::~Encoder(){
    
// }

// float Encoder::getSpeed() const{
//     return info;
// }

// void Encoder::print() const{
//     Serial.println(F("Encoder: "));
//     Serial.print(F("speed = "));
//     Serial.print(getSpeed());
//     Serial.println(F(" m/s"));
// }

// void Encoder::read(){
//     if (millis() - timeold >= 1000)
//     {
//         detachInterrupt(0);
//         if(pulses <= 3)
//             pulses = 0;
//         rpm = (60000/ENCODER_N)/(millis() - timeold)*pulses;
//         timeold = millis();
//         pulses = 0;
//         attachInterrupt(2, counter, FALLING);
//     }
//     info = rpm*PI*CIRCUNFERENCE_DIAMETER/216000.f;
// }

// void Encoder::start(){
//     pinMode(ENCODER_PIN, INPUT);
//     attachInterrupt(2, counter, FALLING);
//     started = true;
// }

// void Encoder::counter(){
//   pulses++;
// }

// volatile byte Encoder::pulses = 0;