// /* Main Arduino Uno */

// #include "ArduinoUnoRX.h"

// ArduinoUnoRX::ArduinoUnoRX():
//     myTransfer(new I2CTransfer())
// {
//     start();
// }

// ArduinoUnoRX::~ArduinoUnoRX(){
//     delete myTransfer;
// }

// void ArduinoUnoRX::print() const{

// }

// void ArduinoUnoRX::receive(){
//     myTransfer->rxObj(arr);
// }

// void ArduinoUnoRX::start(){
//     configST* myConfig = new configST();
//     myConfig->debug = true; 
//     myTransfer->begin(Wire, myConfig);
//     delete myConfig;
//     started = true;
// }