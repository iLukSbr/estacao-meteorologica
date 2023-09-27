#pragma once

#include <SoftwareSerial.h>// UART software interface
#include <TinyGPS++.h>// uBlox GY-GPSV3-NEO-M8N-0-10 GPS
#include <TimeLib.h>// Time zone adjustment

#include "Component.h"

#define ACTUAL_YEAR 2023// Date year validation
#define UTC_OFFSET -3// UTC time zone
#define UTC_GPS_TIME_DRIFT 19// GPS time delayed behind UTC (s)
#define GPS_BAUD_RATE 9600// GPS baud rate
#define GPS_SIZE 6// Sensor data quantity
#define GPS_DECIMAL_PLACES 6// Decimal places for GPS coordinates
#define GPS_MIN_CHARS_PROCESSED 6// Minimum GPS data received to be considered lost information
#define GPS_TX_PIN 3// GPS UART RX pin
#define GPS_RX_PIN 4// GPS UART TX pin

class Gps : public Component{
    private:
        SoftwareSerial* gpsSerial;
        TinyGPSPlus* gps;
        double gps_data[GPS_SIZE] = {0.f};
        bool signal_status;
    
    public:
        Gps();// Create object
        ~Gps();// Release memory

        const bool isSignalAcquired() const;// Check if acquired GPS signal

        const uint16_t getYear() const;// Year
        const uint8_t getMonth() const;// Month
        const uint8_t getDay() const;// Day
        const uint8_t getHour() const;// Hour
        const uint8_t getMinute() const;// Minute
        const uint8_t getSecond() const;// Second

        void gatherDateTime(const bool search);// Get date and time
        void read() override;// Get data from component
        void print() override;// Display data for test
};