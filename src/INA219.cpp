/* Voltage and current sensor INA219 */

#include <INA219.h>

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
    
}

void INA219::start(){
    if(multi->init()){
        started = true;
        multi->setADCMode(SAMPLE_MODE_128);
        multi->setMeasureMode(CONTINUOUS);
        multi->setPGain(amp_def);
        multi->setBusRange(volt_def);
        multi->setCorrectionFactor(calibration_factor);
        multi->setShuntVoltOffset_mV(calibration_volt);
    }
}


void INA219::makeJson(JsonDocument& doc){// Create JSON entries
    if(count == 0)
      doc[F("tensaoEletricaPlacaSolar")] = getVoltage();
    else if(count == 1)
        doc[F("porcentagemBateria")] = getPercentage();
}