#pragma once

// DEFINIÇÕES
#define liga    HIGH
#define desliga LOW

#define UV_PIN A0
#define UV_Serial 9600

#include <Arduino.h>

class UVHandler {
  private: 
    int pinSensorUV;
    int leituraUV;
    byte indiceUV;

  public:
    UVHandler(int pin);
    void begin();
    void printUV();
};