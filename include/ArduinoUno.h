/* Slave Arduino Uno */

#pragma once

#include <SerialTransfer.h>

#include "Component.h"

#ifndef _ARDUINO_UNO
    #define _ARDUINO_UNO
    #define _ARDUINO_UNO_ 1
#endif

#define UNO_RX_PIN 2
#define UNO_TX_PIN 3

class ArduinoUno : public Component{
    private:
        SoftwareSerial* uno;

    public:
        ArduinoUno();
        ~ArduinoUno();

        void print() const override;
        void read() override;
        void start() override;    
}