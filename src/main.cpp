#include <Wire.h>
#include <Arduino_FreeRTOS.h>

#include "componentInclude.h"// enable/disable components there

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// Encoder* speedometer;
// GYNEO6MV2* gps;
// KY015* thermometer;
// KY021* rain_gauge;
// KY36* led;
// MHRTC2* rtc;
// SDReaderWriter* micro_sd;
// MPL3115A2* barometer;
// Relay* relay;
// SolarTracker* solar_tracker;
// TEMT6000* luxmeter0;
// UV* uv_sensor;

unsigned long stopwatch = 0;

Component* storage_array[QUANTITY_OF_COMPONENTS] = {nullptr};
Vector<Component*> component_list(storage_array);

void beginI2C(){
    Wire.begin();
}

void newAll(){
    beginI2C();
    #ifdef _ENCODER
        component_list.push_back(dynamic_cast<Component*>(/*speedometer = */new Encoder()));
    #endif
    #ifdef _GYNEO6MV2
        component_list.push_back(dynamic_cast<Component*>(/*gps = */new GYNEO6MV2()));
    #endif
    #ifdef _KY015
        component_list.push_back(dynamic_cast<Component*>(/*thermometer = */new KY015()));
    #endif
    #ifdef _KY021
        component_list.push_back(dynamic_cast<Component*>(/*rain_gauge = */new KY021()));
    #endif
    #ifdef _KY036
        component_list.push_back(dynamic_cast<Component*>(/*led = */new KY36()));
    #endif
    #ifdef _MHRTC2
        component_list.push_back(dynamic_cast<Component*>(/*rtc = */new MHRTC2()));
    #endif
    #ifdef _MPL3115A2
        component_list.push_back(dynamic_cast<Component*>(/*barometer = */new MPL3115A2()));
    #endif
    #ifdef _RELAY
        component_list.push_back(dynamic_cast<Component*>(/*relay = */new RELAY()));
    #endif
    #ifdef _SD_READER_WRITER
        component_list.push_back(dynamic_cast<Component*>(/*micro_sd = */new SDReaderWriter()));  
    #endif
    #ifdef _SOLAR_TRACKER
        component_list.push_back(dynamic_cast<Component*>(/*solar_tracker = */new SolarTracker()));  
    #endif
    #ifdef _TEMT6000
        component_list.push_back(dynamic_cast<Component*>(/*luxmeter0 = */new TEMT6000()));
    #endif
    #ifdef _UV
        component_list.push_back(dynamic_cast<Component*>(/*uv_sensor = */new UV()));
    #endif
}

void setup(){
    Serial.begin(9600);
    while(!Serial);
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
    delay(10);
}