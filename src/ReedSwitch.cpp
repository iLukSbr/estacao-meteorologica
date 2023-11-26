// /* KY-021 reed switch module for rain sensor tipping bucket */

// #include "pch.h"
// #include "KY021.h"

// KY021::KY021():
//     seesaw_state(false),
//     info(0.f),
//     last_tip(0),
//     rainmeter(new MHRD())
// {
//     start();
// }

// KY021::~KY021(){
//     delete rainmeter;
// }

// float KY021::getRainfall() const{
//     return info;
// }

// void KY021::print() const{
//     Serial.println(F("Pluviometer:"));
//     Serial.print(F("volume = "));
//     Serial.print(info);
//     Serial.println(F(" mm/h"));
// }

// void KY021::read(){
//     bool actual_seesaw_state;
//     long actual_time = millis();
//     long time_span;
//     actual_seesaw_state = ((digitalRead(KY021_PIN) == HIGH) ? true : false);
//     rainmeter->read();
//     if(rainmeter->getRaining()){
//         if(actual_seesaw_state != seesaw_state){
//             time_span = actual_time - last_tip;
//             last_tip = actual_time;
//         }
//     }
//     info = (SEESAW_VOLUME/FUNNEL_AREA)/(time_span/3600000.f);
// }

// void KY021::start(){
//     pinMode(KY021_PIN, INPUT);
//     if(digitalRead(KY021_PIN) == HIGH)
//         seesaw_state = true;
//     else
//         seesaw_state = false;
//     started = true;
//     read();
// }