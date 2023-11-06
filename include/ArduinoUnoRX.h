/* Main Arduino Uno */

#pragma once

#include <I2CTransfer.h>

#include "Component.h"

#define UNO_MAIN
#define MAIN_UNO_I2C_ADDRESS 0x0F
#define DATA_ARRAY_SIZE 50

class ArduinoUnoRX : public Component{
    private:
        I2CTransfer* myTransfer;

        char arr[DATA_ARRAY_SIZE] = {0};

    public:
        ArduinoUnoRX();
        ~ArduinoUnoRX();

        void print() const override;
        void read() override;
        void receive();
        void start() override;    
};