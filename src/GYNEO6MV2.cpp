/* GPS uBlox */

#include "GYNEO6MV2.h"

GYNEO6MV2::GYNEO6MV2():
    gpsSerial(new SoftwareSerial(GPS_RX_PIN, GPS_TX_PIN)),
    gps(new TinyGPSPlus())
{
    start();
}

GYNEO6MV2::~GYNEO6MV2(){

}

const char* GYNEO6MV2::getDateTime() const{
    return date_time;
}

float GYNEO6MV2::getLatitude() const{
    return info[0];
}

float GYNEO6MV2::getLongitude() const{
    return info[1];
}

void GYNEO6MV2::print() const{
    Serial.println(F("GPS:"));
    Serial.print(F("latitude = "));
    Serial.print(getLatitude());
    Serial.println(F("°"));
    Serial.print(F("longitude = "));
    Serial.print(getLongitude());
    Serial.println(F("°"));
    Serial.print(F("date and time UTC = "));
    Serial.println(getDateTime());
}

void GYNEO6MV2::read(){
    while(gpsSerial->available()){
        if(gps->encode(gpsSerial->read())){// Getting data
            if(gps->location.isValid()){
                info[0] = gps->location.lat();// Latitude (°)
                info[1] = gps->location.lng();// Longitude (°)
            }
            if(gps->altitude.isValid())
                info[2] = gps->altitude.meters();// Terrain altitude (m)
            if(gps->speed.isValid())
                info[3] = gps->speed.kmph();// Speed (km/h)
            if(gps->course.isValid())
                info[4] = gps->course.deg();// Course (°)
            if(gps->satellites.isValid())
                info[5] = gps->satellites.value();// Number of GPS satellite signals acquired
        }
    }
    // int year;
    // byte month, day, hour, minute, second, hundredths;
    // gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    // sprintf(date_time, "%02d/%02d/%02d %02d:%02d:%02d ", month, day, year, hour, minute, second);
}

void GYNEO6MV2::start(){
    gpsSerial->begin(GPS_SERIAL_BAUD);
    started = true;
}