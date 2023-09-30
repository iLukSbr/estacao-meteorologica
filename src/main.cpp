#include "UVHandler.h"
#include "GPSHandler.h"

UVHandler uvHandler(UV_PIN);
GPSHandler gpsHandler(GPS_RX, GPS_TX);

void setup() { 
  gpsHandler.begin();
  uvHandler.begin();
}

void loop() {
  uvHandler.printUV();

  if (gpsHandler.newDataAvailable()) {
    gpsHandler.printGPSData();
  }
}