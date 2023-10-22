#include <Wire.h>

#include "componentInclude.h"// enable/disable components there

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// Encoder* speedometer;
// GY511* compass1;
// GYNEO6MV2* gps;
// HMC5883L* compass2;
// KY015* thermometer;
// MHRD* rain_sensor;
// MHRTC2* rtc;
// MPL3115A2* barometer;
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
    #ifdef _GY511
        component_list.push_back(dynamic_cast<Component*>(/*compass1 = */new GY511()));
    #endif
    #ifdef _GYNEO6MV2
        component_list.push_back(dynamic_cast<Component*>(/*gps = */new GYNEO6MV2()));
    #endif
    #ifdef _HMC5883L
        component_list.push_back(dynamic_cast<Component*>(/*compass2 = */new HMC5883L()));
    #endif
    #ifdef _KY015
        component_list.push_back(dynamic_cast<Component*>(/*thermometer = */new KY015()));
    #endif
    #ifdef _MHRD
        component_list.push_back(dynamic_cast<Component*>(/*rain_sensor = */new MHRD()));
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