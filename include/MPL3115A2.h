/* Pressure, altitude and temperature sensor */

#pragma once

#ifndef _MPL3115A2
    #define _MPL3115A2
    #define _MPL3115A2_ 1
#endif

#include <Adafruit_MPL3115A2.h>

#include "Component.h"

#define MPL3115A2_SEA_PRESSURE 1005.05// (hPa) Adjust till altitude is accurate
#define MPL3115A2_PRESSURE_OFFSET 1.f// multiplier, adjust till pressure is accurate
#define MPL3115A2_TEMPERATURE_OFFSET 1.f// multiplier, adjust till temperature is accurate
#define ALTITUDE_KEY "altitude"
#define PRESSURE_KEY "pressure"

class MPL3115A2 : public Component{
    private:
        Adafruit_MPL3115A2* baro;

        float info[3] = {0.f};

    public:
        MPL3115A2();
        ~MPL3115A2();

        float getAltitude() const;
        float getPressure() const;
        float getTemperatureCelsius() const;
        float getTemperatureKelvin() const;

        void makeJson(JsonDocument& doc) override;
        void print() const override;
        void read() override;
        void start() override;
};