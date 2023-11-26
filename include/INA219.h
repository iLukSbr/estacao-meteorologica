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
        byte count;
        
        float info[3];

        INA219_WE* multi;

        INA219_PGAIN amp_def;
        INA219_BUS_RANGE volt_def;
        float calibration_factor;
        float calibration_volt;

    public:
        INA219(byte address, byte _count, INA219_PGAIN _amp_def, INA219_BUS_RANGE _volt_def, float _calibration_factor, float _calibration_voltage);
        ~INA219();

        float getCurrent();
        float getPercentage();
        float getVoltage();

        void print() const override;
        void read() override;
        void start() override;
};