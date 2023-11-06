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

void ArduinoUnoTX::send(char* _arr){
    uint16_t sendSize = 0;
    arr = _arr;
    sendSize = myTransfer->txObj(arr, sendSize);
    myTransfer->sendData(sendSize);
}

void ArduinoUnoTX::start(){
    myTransfer->begin(Wire);
    started = true;
}