/* DHT11 humidity and temperature sensor */

#pragma once

#include <DHT.h>

#include "Component.h"

#define KY015_PIN 2// Digital pin connected to the KY-015 sensor
#define KY015_TYPE DHT11
#define KY015_HUMIDITY_OFFSET 28.0// (%) Adjust till humidity is accurate
#define KY015_TEMPERATURE_OFFSET -1.5// (°C) Adjust till temperature is accurate

class KY015 : public Component{
    private:
        DHT* dht;

        float info[3] = {0.f};

    public:
        KY015();
        ~KY015();

        float getHumidity() const;
        float getTemperatureCelsius() const;
        float getTemperatureKelvin() const;
        float getHeatIndexCelsius() const;
        float getHeatIndexKelvin() const;

        void print() const;
        void read();
        void start();
};