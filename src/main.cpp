#include "pch.h"

#include <Wire.h>

#include "componentInclude.h"// enable/disable components there

#define SEND_JSON_DELAY 60000// ms

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// Encoder* speedometer;
// ESP01* wifi;
// GYNEO6MV2* gps;
// INA219 *multimeter_solar, *multimeter_batteries;
// KY015* thermometer;
// KY021* rain_gauge;
// TTP223B* led;
// MHRTC2* rtc;
// SDReaderWriter* micro_sd;
// MPL3115A2* barometer;
Relay* relay;
// SolarTracker* solar_tracker;
// TEMT6000* luxmeter0;
// UV* uv_sensor;

unsigned long stopwatch = 0;

Component* storage_array[QUANTITY_OF_COMPONENTS+1] = {nullptr};
Vector<Component*> component_list(storage_array);

void beginI2C(){
        Wire.begin();
}

void newAll(){
    beginI2C();
    // #ifdef _WIND_VANE
        // component_list.push_back(dynamic_cast<Component*>(/*magnetometer = */new GY511()));
    // #endif
    #ifdef _ENCODER
        component_list.push_back(dynamic_cast<Component*>(/*speedometer = */new Encoder()));
    #endif
    #ifdef _GYNEO6MV2
        component_list.push_back(dynamic_cast<Component*>(/*gps = */new GYNEO6MV2()));
    #endif
    #ifdef _INA219
        // component_list.push_back(dynamic_cast<Component*>(/*multimeter_solar = */new INA219(0x40, 0, PG_80, BRNG_16, 1.f, 1.f)));
        // component_list.push_back(dynamic_cast<Component*>(/*multimeter_batteries = */new INA219(0x41, 1, PG_160, BRNG_32, 1.f, 1.f)));
    #endif
    #ifdef _KY015
        component_list.push_back(dynamic_cast<Component*>(/*thermometer = */new KY015()));
    #endif
    #ifdef _KY021
        component_list.push_back(dynamic_cast<Component*>(/*rain_gauge = */new KY021()));
    #endif
    #ifdef _MHRTC2
        component_list.push_back(dynamic_cast<Component*>(/*rtc = */new MHRTC2()));
    #endif
    #ifdef _MPL3115A2
        component_list.push_back(dynamic_cast<Component*>(/*barometer = */new MPL3115A2()));
    #endif
    #ifdef _SOLAR_TRACKER
        component_list.push_back(dynamic_cast<Component*>(/*solar_tracker = */new SolarTracker()));  
    #endif
    #ifdef _TEMT6000
        component_list.push_back(dynamic_cast<Component*>(/*luxmeter0 = */new TEMT6000()));
    #endif
    #ifdef _TTP223B
        component_list.push_back(dynamic_cast<Component*>(/*led = */new TTP223B()));
    #endif
    #ifdef _UV
        component_list.push_back(dynamic_cast<Component*>(/*uv_sensor = */new UV()));
    #endif
}

String makeJson(){
    StaticJsonDocument<1000> doc;
    String doc_serialized;
    for(auto element : component_list)
        if(element->isStarted())
            element->makeJson(doc);
    serializeJson(doc, doc_serialized);
    return doc_serialized;
}

void setup(){
    Serial.begin(9600);
    while(!Serial);
    relay->on();
    relay->print();
    newAll();
}

void loop(){
    for(auto element : component_list){
        if(element->isStarted()){
            if(element->verifyDelay()){
                element->read();
                element->print();
                Serial.println();
            }
        }
        else
            element->start();
    }
    if(millis() - stopwatch > SEND_JSON_DELAY || !stopwatch){
        String json_str = makeJson();
        // micro_sd->save(json_str);
        // wifi->sendJson(json_str);
        Serial.println(json_str);
        Serial.println();
        stopwatch = millis();
    }
    delay(1000);
}