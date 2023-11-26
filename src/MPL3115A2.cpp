/* Pressure, altitude and temperature sensor */

#include "pch.h"
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

float MPL3115A2::getAltitude() const{
    return info[0];
}

float MPL3115A2::getPressure() const{
    return info[1];
}

float MPL3115A2::getTemperatureCelsius() const{
    return info[2];
}

float MPL3115A2::getTemperatureKelvin() const{
    return info[2] + 273.15;
}

void MPL3115A2::makeJson(JsonDocument& doc){
    doc[F(ALTITUDE_KEY)] = getAltitude();
    doc[F(PRESSURE_KEY)] = getPressure();
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
}

void MPL3115A2::read(){
    info[0] = baro->getAltitude();
    info[1] = 100*(baro->getPressure()*MPL3115A2_PRESSURE_OFFSET);
    info[2] = baro->getTemperature()*MPL3115A2_TEMPERATURE_OFFSET;
}

void MPL3115A2::start(){
    for(byte i=0; i<START_TRIES; i++){
        delay(LOOP_DELAY);
        if(baro->begin() && !isnan(baro->getPressure()) && !isnan(baro->getTemperature()) && !isnan(baro->getAltitude())){
            started = true;
            return;
        }
    }
}


void MPL3115A2::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F("pressao")] = getPressure();
    doc[F("altitude")] = getAltitude();
}