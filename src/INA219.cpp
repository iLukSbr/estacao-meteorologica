/* Voltage and current sensor INA219 */

#include <INA219.h>

INA219::INA219():
    multi(new INA219_WE(INA219_I2C_ADDRESS))
{
    start();
}

INA219::INA219(){
    
}

float INA219::getCurrent(){
    return info[0];
}

float INA219::getPercentage(){
    rerurn info[1];
}

float INA219::getVoltage(){
    return info[2];
}

void INA219::print() const{
    Serial.print(F("INA219 "));
    Serial.print(name);
    Serial.println(F(:));
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
        multi->setADCMode(SAMPLE_MODE_128)
        multi->setMeasureMode(CONTINUOUS);
        multi->setPGain(amp_def);
        multi->setBusRange(volt_def);
        multi->setCorrectionFactor(calibration_factor);
        multi->setShuntVoltOffset(calibration_volt);
    }
}


void INA219::makeJson(JsonDocument& doc){// Create JSON entries
    if(count == 0)
      doc[F("tensaoEletricaPlacaSolar")] = getVoltage();
    else if(count == 1)
        doc[F("porcentagemBateria")] = getPercentage();
}