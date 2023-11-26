/*
MIT License

Copyright (c) 2023 Lucas Yukio Fukuda Matsumoto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "pch.h"
#include "GYNEO6MV2.h"

GYNEO6MV2::GYNEO6MV2():
    signal_status(false),
    gps(new TinyGPSPlus())
{// Create object
    Serial2.begin(GPS_BAUD_RATE);// Serial baud rate
    start();
}

GYNEO6MV2::~GYNEO6MV2(){// Release memory
    delete gps;
}

void GYNEO6MV2::read(){// Get data from component
    Serial.println(F("Reading GY-NEO6MV2 GPS..."));
    uint16_t i = 0;
    info[0] = DEFAULT_LATITUDE;
    info[1] = DEFAULT_LONGITUDE;
    while(Serial2.available() > 0){
        if(gps->encode(Serial2.read())){// Getting data
            if (gps->location.isValid()){
                info[0] = gps->location.lat();// Latitude (°)
                info[1] = gps->location.lng();// Longitude (°)
                if((info[0] < 1.f && info[0] > -1.f) || (info[1] < 1.f && info[1] > -1.f)){
                    info[0] = DEFAULT_LATITUDE;
                    info[1] = DEFAULT_LONGITUDE;
                }
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
        if(i > 5*LOOP_DELAY && gps->charsProcessed() < GPS_MIN_CHARS_PROCESSED){// If data is not valid
            Serial.println(F("GPS signal not detected."));
            break;
        }
        i++;
    }
}

void GYNEO6MV2::print() const{// Display data for test
    Serial.println(F("NEO-M8N GPS: "));
    Serial.print(F("latitude = "));
    Serial.print(info[0], GPS_DECIMAL_PLACES);
    Serial.println(F("°"));
    Serial.print(F("logitude = "));
    Serial.print(info[1], GPS_DECIMAL_PLACES);
    Serial.println(F("°"));
    Serial.print(F("surface altitude = "));
    Serial.print(info[2]);
    Serial.println(F(" m"));
    Serial.print(F("speed = "));
    Serial.print(info[3]);
    Serial.println(F(" km/h"));
    Serial.print(F("course = "));
    Serial.print(info[4]);
    Serial.println(F("°"));
    Serial.print(F("satellites = "));
    Serial.println(info[5]);
}

void GYNEO6MV2::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F(LATITUDE_KEY)] = serialized(String(info[0],6));
    doc[F(LONGITUDE_KEY)] = serialized(String(info[1],6));
}

const uint16_t GYNEO6MV2::getYear() const{
    return year();
}

const uint8_t GYNEO6MV2::getMonth() const{
    return month();
}

const uint8_t GYNEO6MV2::getDay() const{
    return day();
}

const uint8_t GYNEO6MV2::getHour() const{
    return hour();
}

const uint8_t GYNEO6MV2::getMinute() const{
    return minute();
}

const uint8_t GYNEO6MV2::getSecond() const{
    return second();
}

void GYNEO6MV2::gatherDateTime(const bool search){// Get date and time, keep searching signal if true
    uint8_t i = 0;
    Serial.println(F("Searching for GPS signal..."));
    do{
        read();
        i++;
        if(i>START_TRIES && !search){
            info[0] = DEFAULT_LATITUDE;
            info[1] = DEFAULT_LONGITUDE;
            Serial.println(F("GPS signal not found, timeout!"));
            return;
        }
        delay(LOOP_DELAY);
    }while((!gps->date.isValid() || !gps->time.isValid()) || gps->date.year()>ACTUAL_YEAR);// Colecting date and time
    if(!isStarted())
        started = true;
    if(!signal_status)
        signal_status = true;
    setTime(gps->time.hour(), gps->time.minute(), gps->time.second() + UTC_GPS_TIME_DRIFT, gps->date.day(), gps->date.month(), gps->date.year());
    adjustTime(UTC_OFFSET*SECS_PER_HOUR);
    delay(LOOP_DELAY);
}

void GYNEO6MV2::start(){
    Serial.println(F("Starting GY-NEO6MV2 GPS..."));
    gatherDateTime(false);
    if(isStarted())
        Serial.println(F("GY-NEO6MV2 GPS OK!"));
}

const bool GYNEO6MV2::isSignalAcquired() const{
    return signal_status;
}