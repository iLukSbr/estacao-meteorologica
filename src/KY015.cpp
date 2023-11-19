/* DHT11 humidity and temperature sensor */

#include "KY015.h"

KY015::KY015():
    dht(new DHT(KY015_PIN, KY015_TYPE))
{
    start();
}

KY015::~KY015(){
    delete dht;
}

float KY015::getHumidity() const{
    return info[0];
}

float KY015::getTemperatureCelsius() const{
    return info[1];
}

float KY015::getTemperatureKelvin() const{
    return info[1] + 273.15;
}

float KY015::getHeatIndexCelsius() const{
    return info[2];
}

float KY015::getHeatIndexKelvin() const{
    return info[2] + 273.15;
}

void KY015::print() const{
    Serial.println(F("KY015:"));
    Serial.print(F("humidity = "));
    Serial.print(getHumidity());
    Serial.println(F(" %"));
    Serial.print(F("temperature = "));
    Serial.print(getTemperatureCelsius());
    Serial.print(F(" °C = "));
    Serial.print(getTemperatureKelvin());
    Serial.println(F(" K"));
    Serial.print(F("heat index = "));
    Serial.print(getHeatIndexCelsius());
    Serial.print(F(" °C = "));
    Serial.print(getHeatIndexKelvin());
    Serial.println(F(" K"));
}

void KY015::read(){
    info[0] = constrain(dht->readHumidity() + KY015_HUMIDITY_OFFSET,0.f,100.f);
    info[1] = dht->readTemperature() + KY015_TEMPERATURE_OFFSET;
    info[2] = dht->computeHeatIndex(info[1],info[0],false);
}

void KY015::start(){
    for(uint8_t i=0; i<START_TRIES; i++){
        dht->begin();
        if(!isnan(dht->readHumidity()) && !isnan(dht->readTemperature())){
            started = true;
            return;
        }
    }
}


void KY015::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F("temperatura")] = getTemperature();
    doc[F("umidade")] = getHumidity();
}