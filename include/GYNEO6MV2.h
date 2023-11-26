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

#pragma once

#include "Component.h"

// uBlox GY-NEO6MV2 GPS
// https://github.com/mikalhart/TinyGPSPlus
#include <TinyGPS++.h>

// Time zone adjustment
// https://github.com/PaulStoffregen/Time
#include <TimeLib.h>

#ifndef _GYNEO6MV2
#define _GYNEO6MV2
  #define _GYNEO6MV2_ 1
#endif

#define DEFAULT_LATITUDE -25.439733
#define DEFAULT_LONGITUDE -49.268210
#define ACTUAL_YEAR 2023// Date year validation
#define UTC_OFFSET -3// UTC time zone
#define UTC_GPS_TIME_DRIFT 19// (s) GPS time delayed behind UTC
#define GPS_BAUD_RATE 9600// GPS baud rate
#define GPS_DECIMAL_PLACES 6// Decimal places for GPS coordinates
#define GPS_MIN_CHARS_PROCESSED 6// Minimum GPS data received to be considered lost information
#define LATITUDE_KEY "latitude"// JSON latitude key
#define LONGITUDE_KEY "longitude"// JSON longitude key

class GYNEO6MV2 : public Component{
  private:
    bool signal_status;

    float info[6] = {0.f};

    TinyGPSPlus* gps;
    
  public:
    GYNEO6MV2();// Create object
    ~GYNEO6MV2();// Release memory

    const bool isSignalAcquired() const;// Check if acquired GPS signal

    void gatherDateTime(const bool search);// Get date and time
    void makeJson(JsonDocument& doc) override;// Create JSON entries
    void print() const override;// Display data for test
    void read() override;// Get data from component   
    void start() override;

    const uint8_t getMonth() const;// Month
    const uint8_t getDay() const;// Day
    const uint8_t getHour() const;// Hour
    const uint8_t getMinute() const;// Minute
    const uint8_t getSecond() const;// Second

    const uint16_t getYear() const;// Year   
};