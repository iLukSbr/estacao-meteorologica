/* Main Arduino Uno */

#pragma once

#include <I2CTransfer.h>

#include "Component.h"

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
}