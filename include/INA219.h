/* Voltage and current sensor INA219 */

#pragma once

#include <INA219_WE.h>

#include "Component.h"

#ifndef _INA219
    #define _INA219
    #define _INA219_ 1
#endif

#define INA219_I2C_ADDRESS 0x40

class INA219 : public Component{
    private:
        float info[3];

        INA219_WE* multi;

    public:
        INA219(INA219_PGAIN );
        ~INA219();

        float getCurrent();
        float getPercentage();
        float getVoltage();

        void print() const override;
        void read() override;
        void start() override;
};