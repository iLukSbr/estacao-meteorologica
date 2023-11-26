/* MH-Real Time Clock 2  DS1302*/

#include "pch.h"
#include "MHRTC2.h"

MHRTC2::MHRTC2():
    rtc(new DS1302(RTC_RST_PIN, RTC_CLK_PIN, RTC_DAT_PIN))// Init rtc object DS1302 rtc(ce_pin, sck_pin, io_pin);
{
    start();
}

MHRTC2::~MHRTC2(){
    delete rtc;
}

const char* MHRTC2::getDateTime() const{
    return info;
}

void MHRTC2::print() const{
    Serial.println(F("MH-RTC 2:"));
    Serial.print(F("date and time = "));
    Serial.println(getDateTime());
}

void MHRTC2::read() {
    DateTime now = rtc->now();
    now.tostr(info);
}

void MHRTC2::start(){
    rtc->begin();
    rtc->adjust(DateTime(__DATE__, __TIME__));// sets the RTC to the date & time this sketch was compiled
    started = true;
}