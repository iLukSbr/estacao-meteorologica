/* Slave Arduino Uno */

#include "ArduinoUnoTX.h"

ArduinoUnoTX::ArduinoUnoTX():
    myTransfer(new I2CTransfer()))
{
    start();
}

ArduinoUnoTX::~ArduinoUnoTX(){
    delete myTransfer;
}

void ArduinoUnoTX::print() const{

}

void ArduinoUnoTX::send() const{
    uint16_t sendSize = 0;
    sendSize = myTransfer->txObj(arr, sendSize);
    myTransfer->sendData(sendSize);
}

void ArduinoUnoTX::start(){
    myTransfer->begin(Wire);
    started = true;
}