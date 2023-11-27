/* Voltage and current sensor INA219 */

#include "pch.h"
#include "INA219.h"

INA219::INA219(byte address, byte _count, INA219_PGAIN _amp_def, INA219_BUS_RANGE _volt_def, float _calibration_factor, float _calibration_volt):
    count(_count),
    multi(new INA219_WE(address)),
    amp_def(_amp_def),
    volt_def(_volt_def),
    calibration_factor(_calibration_factor),
    calibration_volt(_calibration_volt)
{
    start();
}

INA219::~INA219(){
    
}

float INA219::getCurrent(){
    return info[0];
}

float INA219::getPercentage(){
    return info[1];
}

float INA219::getVoltage(){
    return info[2];
}

void INA219::print() const{
    Serial.print(F("INA219 "));
    Serial.print(count);
    Serial.println(F(":"));
    Serial.print(F("current = "));
    Serial.println(info[0]);
    Serial.print(F("percentage = "));
    Serial.println(info[1]);
    Serial.print(F("voltage = "));
    Serial.println(info[2]);
}

void INA219::read(){
    Serial.println(F("Reading INA219 multimeter..."));
    info[0] = multi->getCurrent_mA();
    info[2] = multi->getBusVoltage_V() + multi->getShuntVoltage_mV()/1000.f;
    if(count == 0)
        info[1] = 100.f*info[2]/12.f;
    else if(count == 1)
        info[1] = 100.f*(info[2]-12.f)/(16.8f-12.f);
}

void INA219::start(){
    Serial.println(F("Starting INA219 multimeter..."));
    if(multi->init()){
        started = true;
        multi->setADCMode(SAMPLE_MODE_128);
        multi->setMeasureMode(CONTINUOUS);
        multi->setPGain(amp_def);
        multi->setBusRange(volt_def);
        multi->setCorrectionFactor(calibration_factor);
        multi->setShuntVoltOffset_mV(calibration_volt);
        Serial.println(F("INA219 multimeter OK!"));
    }
    else
        Serial.println(F("INA219 multimeter failed."));
}

void INA219::makeJson(JsonDocument& doc){// Create JSON entries
    if(count == 0)
      doc[F(SOLAR_VOLTAGE_KEY)] = getVoltage();
    else if(count == 1)
        doc[F(BATTERY_PERCENTAGE_KEY)] = getPercentage();
}