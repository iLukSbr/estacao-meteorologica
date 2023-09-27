#include "MPL3115A2.h"

MPL3115A2::MPL3115A2():
    baro(new Adafruit_MPL3115A2())
{
    start();
    baro->setSeaPressure(MPL3115A2_SEA_PRESSURE);
}

MPL3115A2::~MPL3115A2(){
    delete baro;
}

bool MPL3115A2::isStarted() const{
    return started;
}

float MPL3115A2::getAltitude() const{
    return data[0];
}

float MPL3115A2::getPressure() const{
    return data[1];
}

float MPL3115A2::getTemperatureCelsius() const{
    return data[2];
}

float MPL3115A2::getTemperatureKelvin() const{
    return data[3];
}

void MPL3115A2::print() const{
    Serial.println(F("MPL3115A2:"));
    Serial.print(F("pressure = "));
    Serial.print(getPressure());
    Serial.println(F(" Pa"));
    Serial.print(F("altitude = "));
    Serial.print(getAltitude());
    Serial.println(F(" m"));
    Serial.print(F("temperature = "));
    Serial.print(getTemperatureCelsius());
    Serial.print(F(" °C = "));
    Serial.print(getTemperatureKelvin());
    Serial.println(F(" K"));
    Serial.println(F("========================================"));
}

void MPL3115A2::read(){
    data[0] = baro->getAltitude();
    data[1] = 100*(baro->getPressure() + MPL3115A2_PRESSURE_OFFSET);
    data[2] = baro->getTemperature() + MPL3115A2_TEMPERATURE_OFFSET;
    data[3] = data[2] + 273.15;
}

void MPL3115A2::start(){
    for(uint8_t i=0; i<START_TRIES; i++){
        delay(LOOP_DELAY);
        if(baro->begin() && !isnan(baro->getPressure()) && !isnan(baro->getTemperature()) && !isnan(baro->getAltitude())){
            started = true;
            return;
        }
    }
}