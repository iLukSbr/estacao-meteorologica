#pragma once

#include <Adafruit_MPL3115A2.h>

#include "Component.h"

#define MPL3115A2_SEA_PRESSURE 1005.05// (hPa) Adjust till altitude is accurate
#define MPL3115A2_PRESSURE_OFFSET 2.8// (hPa) Adjust till pressure is accurate
#define MPL3115A2_TEMPERATURE_OFFSET -1.4// (°C) Adjust till temperature is accurate

class MPL3115A2 : public Component{
    private:
        Adafruit_MPL3115A2* baro;

        float info[4] = {0.f};

    public:
        MPL3115A2();
        ~MPL3115A2();

        float getAltitude() const;
        float getPressure() const;
        float getTemperatureCelsius() const;
        float getTemperatureKelvin() const;

        void print() const override;
        void read() override;
        void start() override;
};