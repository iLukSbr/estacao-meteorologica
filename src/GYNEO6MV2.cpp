/* GPS uBlox */

#include "GYNEO6MV2.h"

SoftwareSerial gpsSerial(GPS_RX_PIN, GPS_TX_PIN);// RX pin, TX pin

GYNEO6MV2::GYNEO6MV2()
{
    start();
}

GYNEO6MV2::~GYNEO6MV2(){

}

// const char* GYNEO6MV2::getDateTime() const{
//     return date_time;
// }

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
    // Serial.print(F("date and time UTC = "));
    // Serial.println(getDateTime());
}

void GYNEO6MV2::read(){
    while(gpsSerial.available())
        gps.encode(gpsSerial.read());
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    info[0] = flat;
    info[1] = flon;
    // int year;
    // byte month, day, hour, minute, second, hundredths;
    // gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
    // sprintf(date_time, "%02d/%02d/%02d %02d:%02d:%02d ", month, day, year, hour, minute, second);
}

void GYNEO6MV2::start(){
    gpsSerial.begin(GPS_SERIAL_BAUD);
    started = true;
}