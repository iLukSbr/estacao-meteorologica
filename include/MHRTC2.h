/* Clock */

#pragma once

#include "Component.h"

#include <RTClib.h>

#include "MHRTC2.h"

class MHRTC2 : public Component{
  private:
    RTC_DS1307 *rtc;
    char clock_data[21] = {0};
    char *day_of_the_week;
    char days[7][14] = {0};
    
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