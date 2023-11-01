/* Slave Arduino Uno */

#include "ArduinoUno.h"

ArduinoUno::ArduinoUno():
    uno(new SoftwareSerial(UNO_RX_PIN, UNO_TX_PIN))
{

}

ArduinoUno::~ArduinoUno(){

}

void ArduinoUno::print() const{
    
}

void ArduinoUno::start(){
    pinMode(UNO_RX_PIN, INPUT);
    pinMode(UNO_TX_PIN, OUTPUT);
    uno->begin(9600);
    started = true;
}