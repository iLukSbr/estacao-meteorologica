/* Main Arduino Uno */

#include "ArduinoUnoRX.h"

ArduinoUnoRX::ArduinoUnoRX():
    myTransfer(new I2CTransfer()))
{
    start();
}

ArduinoUnoRX::~ArduinoUnoRX(){
    delete myTransfer;
}

void ArduinoUnoRX::print() const{

}

void ArduinoUnoRX::receive() const{
    myTransfer->rxObj(arr);
}

void ArduinoUnoRX::start(){
    configST* myConfig = new configST();
    myConfig->debug = true;
    myConfig->callbacks = callbackArr;
    myConfig->callbacksLen = sizeof(callbackArr)/sizeof(functionPtr);  
    myTransfer->begin(Wire, myConfig);
    delete myConfig;
    started = true;
}