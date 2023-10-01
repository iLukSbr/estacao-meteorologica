/* GPS uBlox */

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define GPS_RX 4
#define GPS_TX 3
#define GPS_Serial_Baud 9600

class GYNEO6MV2{
private:
  TinyGPS gps;
  SoftwareSerial gpsSerial;

public:
  GYNEO6MV2(int rxPin, int txPin);
  void begin();
  bool newDataAvailable();
  void printGPSData();
};