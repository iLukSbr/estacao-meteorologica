/* Slave Arduino Uno */

#pragma once

#include "Component.h"

#ifndef _ARDUINO_UNO
    #define _ARDUINO_UNO
    #define _ARDUINO_UNO_ 1
#endif

class ArduinoUno : public Component{
    private:

    public:
        ArduinoUno();
        ~ArduinoUno();

        void print() const override;
        void read() override;
        void start() override;    
}