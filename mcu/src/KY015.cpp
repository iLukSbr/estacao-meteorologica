#include "KY015.h"

KY015::KY015():
    dht(new DHT(KY015_PIN, KY015_TYPE))
{
    start();
}

KY015::~KY015(){
    delete dht;
}

bool KY015::isStarted() const{
    return started;
}

float KY015::getHumidity() const{
    return data[0];
}

float KY015::getTemperatureCelsius() const{
    return data[1];
}

float KY015::getTemperatureKelvin() const{
    return data[2];
}

float KY015::getHeatIndexCelsius() const{
    return data[3];
}

float KY015::getHeatIndexKelvin() const{
    return data[4];
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
    Serial.println(F("========================================"));
}

void KY015::read(){
    data[0] = constrain(dht->readHumidity() + KY015_HUMIDITY_OFFSET,0.f,100.f);
    data[1] = dht->readTemperature() + KY015_TEMPERATURE_OFFSET;
    data[2] = data[1] + 273.15;
    data[3] = dht->computeHeatIndex(data[1],data[0],false);
    data[4] = data[3] + 273.15;
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