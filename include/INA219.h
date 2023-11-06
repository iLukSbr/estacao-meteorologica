/* Voltage and current sensor INA219 */

#pragma once

#include <INA219_WE.h>

#include "Component.h"

#ifndef _INA219
    #define _INA219
    #define _INA219_ 1
#endif

#define SHUNT_RESISTANCE 100

class INA219 : public Component{
    private:
        byte count;
        
        float info[3];

        INA219_WE* multi;

    public:
        INA219(byte address);
        ~INA219();

        float getCurrent();
        float getPercentage();
        float getVoltage();

        void print() const override;
        void read() override;
        void start() override;
};