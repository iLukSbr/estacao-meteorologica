/* MH-Real Time Clock 2  DS1302*/

#include "pch.h"
#include "MHRTC2.h"

#define countof(a) (sizeof(a) / sizeof(a[0]))

MHRTC2::MHRTC2():
    myWire(new ThreeWire(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN)),// Init rtc pin (ce_pin, sck_pin, io_pin);
    rtc(new RtcDS1302<ThreeWire>(*myWire))
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

void MHRTC2::read(){
    RtcDateTime now = rtc->GetDateTime();
    if(!now.IsValid()){
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }
    makeDateTime(now);
}

void MHRTC2::start(){
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    rtc->Begin();
    if (rtc->GetIsWriteProtected()){
        Serial.println(F("RTC was write protected, enabling writing now."));
        rtc->SetIsWriteProtected(false);
    }
    if (!rtc->GetIsRunning()){
        Serial.println(F("RTC was not actively running, starting now."));
        rtc->SetIsRunning(true);
    }
    rtc->SetDateTime(compiled);// sets the RTC to the date & time this sketch was compiled
    started = true;
}

void MHRTC2::makeDateTime(const RtcDateTime& dt){
    snprintf_P(info, 
            countof(info),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
}