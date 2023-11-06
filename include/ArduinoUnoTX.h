/* Slave Arduino Uno */

#pragma once

#include <I2CTransfer.h>

#include "Component.h"

class ArduinoUnoTX : public Component{
    private:
        I2CTransfer* myTransfer;

        char arr[DATA_ARRAY_SIZE] = {0};

    public:
        ArduinoUnoTX();
        ~ArduinoUnoTX();

        void print() const override;
        void read() override;
        void send();
        void start() override;    
}