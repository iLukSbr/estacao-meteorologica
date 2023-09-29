#pragma once

#include "Component.h"

// DS3231 RTC
// https://github.com/adafruit/RTClib
#include <RTClib.h>// I²C address 0x57 (EEPROM) and 0x68 (RTC)

#include "Gps.h"

#define RTCLOCK_SIZE 21// Date and time string length
#define DATE_TIME_KEY "id"// JSON date and time key
#define DAY_OF_THE_WEEK_KEY "dia da semana"// JSON day of the week key
#define PT_BR// Português brasileiro
// #define EN_US// Inglês

class RTClock : public Component{
  private:
    RTC_DS3231 *rtc;
    char clock_data[RTCLOCK_SIZE] = {0};
    char *day_of_the_week;
    #ifdef EN_US
      char days[7][14] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    #else
      char days[7][14] = {"Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado"};
    #endif
    
  public:
    RTClock(const uint16_t& year, const uint8_t& month, const uint8_t& day, const uint8_t& hour, const uint8_t& minute, const uint8_t& second);// Create object
    RTClock();
    ~RTClock();// Release memory
    void gatherData() override;// Get data from component
    void printData() override;// Display data for test
    void makeJSON(const bool& isHTTP, JsonDocument& doc, JsonObject& payload) override;// Create JSON entries
    void saveCSVToFile(SdFile* my_file) override;// Save data to MicroSD card
    char* getDateTime();// Date and time
    bool checkValidDate(const uint16_t& minute);// If date is valid
    void rtcAdjust(const uint16_t& year, const uint8_t& month, const uint8_t& day, const uint8_t& hour, const uint8_t& minute, const uint8_t& second);
};