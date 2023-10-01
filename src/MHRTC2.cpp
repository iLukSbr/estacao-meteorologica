/* Clock */

#include "RTClock.h"

RTClock::RTClock():
    rtc(new RTC_DS1307()),// Instatiate RTC
    day_of_the_week(nullptr),
    days({"Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado"})
{// Create object
    while(!rtc->begin()){
    }
}

RTClock::RTClock(const uint16_t& year, const uint8_t& month, const uint8_t& day, const uint8_t& hour, const uint8_t& minute, const uint8_t& second):
    rtc(new RTC_DS1307()),// Instatiate RTC
    day_of_the_week(nullptr),
    days({"Domingo", "Segunda-feira", "Terça-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "Sábado"})
{// Create object
    multiPrintln(F("Starting RTC..."));
    while(!rtc->begin()){
        multiPrintln(F("Waiting for RTC..."));
        delay(CALIBRATION_DELAY);
    }
    rtcAdjust(year, month, day, hour, minute, second);
    multiPrintln(F("RTClock OK!"));
}

RTClock::~RTClock(){// Release memory
    delete rtc;
}

void RTClock::gatherData(){// Get data from component
    multiPrintln(F("Gathering RTClock data..."));
    DateTime now = rtc->now();// Get real time
    day_of_the_week = days[now.dayOfTheWeek()];
    snprintf_P(clock_data,
               21,
               PSTR("%02u-%02u-%04u_%02u-%02u-%02u"),// Date-hour format
               now.day(),// Day
               now.month(),// Month
               now.year(),// Year
               now.hour(),// Hour
               now.minute(),// Minutes
               now.second());// Seconds
}

void RTClock::printData(){// Display data for test
    multiPrint(F("RTClock: "));
    multiPrint(clock_data);
    multiPrintln();
}

void RTClock::makeJSON(const bool& isHTTP, JsonDocument& doc, JsonObject& payload){// Create JSON entries
    if(!isHTTP){
        doc[F(DATE_TIME_KEY)] = clock_data;
        payload[F(DAY_OF_THE_WEEK_KEY)] = day_of_the_week;
    }
}

void RTClock::saveCSVToFile(SdFile* my_file){// Save data to MicroSD card
    my_file->print(clock_data);
    my_file->print(F(","));
}

char* RTClock::getDateTime(){// Date and time
    gatherData();
    return clock_data;
}

bool RTClock::checkValidDate(const uint16_t& minute){// Check if date is valid
    if(rtc->now().day()>0 && rtc->now().minute()==minute)
        return true;
    return false;
}

void RTClock::rtcAdjust(const uint16_t& year, const uint8_t& month, const uint8_t& day, const uint8_t& hour, const uint8_t& minute, const uint8_t& second){
    rtc->adjust(DateTime(year, month, day, hour, minute, second));
}

MPL3115A2::MPL3115A2():
    baro(new Adafruit_MPL3115A2())
{
    start();
    baro->setSeaPressure(MPL3115A2_SEA_PRESSURE);
}

MPL3115A2::~MPL3115A2(){
    delete baro;
}

bool MPL3115A2::isStarted() const{
    return started;
}

float MPL3115A2::getAltitude() const{
    return info[0];
}

float MPL3115A2::getPressure() const{
    return info[1];
}

float MPL3115A2::getTemperatureCelsius() const{
    return info[2];
}

float MPL3115A2::getTemperatureKelvin() const{
    return info[3];
}

void MPL3115A2::print() const{
    Serial.println(F("MPL3115A2:"));
    Serial.print(F("pressure = "));
    Serial.print(getPressure());
    Serial.println(F(" Pa"));
    Serial.print(F("altitude = "));
    Serial.print(getAltitude());
    Serial.println(F(" m"));
    Serial.print(F("temperature = "));
    Serial.print(getTemperatureCelsius());
    Serial.print(F(" °C = "));
    Serial.print(getTemperatureKelvin());
    Serial.println(F(" K"));
    Serial.println(F("========================================"));
}

void MPL3115A2::read(){
    info[0] = baro->getAltitude();
    info[1] = 100*(baro->getPressure() + MPL3115A2_PRESSURE_OFFSET);
    info[2] = baro->getTemperature() + MPL3115A2_TEMPERATURE_OFFSET;
    info[3] = info[2] + 273.15;
}