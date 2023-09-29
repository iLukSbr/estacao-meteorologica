#pragma once

// DEFINIÇÕES
#define liga    HIGH
#define desliga LOW

#include <Arduino.h>

class uv {
  public:
    uv(int pin);
    void show();
  private: 
    int pinSensorUV;
    int leituraUV;
    byte indiceUV;
};