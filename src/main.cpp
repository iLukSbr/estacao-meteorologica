#include <Vector.h>

/* Comment the header to disable the component
   Uncomment the header to enable the component */
#include "GY511.h"
#include "GYNEO6MV2.h"
#include "HMC5883L.h"
#include "I2CServoDriver.h"
#include "KY015.h"
#include "LDR.h"
#include "MHRD.h"
#include "MHRTC2.h"
#include "MPL3115A2.h"
#include "ITGMPU6050.h"
#include "Encoder.h"
#include "TEMT6000.h"
#include "UV.h"

#define QUANTITY_OF_COMPONENTS 13
#define READING_DELAY 3000// (ms) Delay between readings

unsigned long stopwatch = 0;

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// GY511* compass1;
// GYNEO6MV2* gps;
// HMC5883L* compass2;
// I2CServoDriver* servo;
// KY015* thermometer;
// LDR* luxmeter1;
// MHRD* rain_sensor;
// MHRTC2* rtc;
// MPL3115A2* barometer;
// ITGMPU6050* gyroscope;
// Encoder* speedometer;
// TEMT6000* luxmeter0;
// UV* uv_sensor;

Component* storage_array[QUANTITY_OF_COMPONENTS] = {nullptr};
Vector<Component*> component_list(storage_array);

void newAll(){
    #ifdef GY511
        component_list.push_back(dynamic_cast<Component*>(/*compass1 = */new GY511()));
    #endif
    #ifdef GYNEO6MV2
        component_list.push_back(dynamic_cast<Component*>(/*gps = */new GYNEO6MV2()));
    #endif
    #ifdef HMC5883L
        component_list.push_back(dynamic_cast<Component*>(/*compass2 = */new HMC5883L()));
    #endif
    #ifdef I2CSERVODRIVER
        component_list.push_back(dynamic_cast<Component*>(/*servo = */new I2CServoDriver()));
    #endif
    #ifdef LDR
        component_list.push_back(dynamic_cast<Component*>(/*luxmeter1 = */new LDR(A2)));
    #endif
    #ifdef KY015
        component_list.push_back(dynamic_cast<Component*>(/*thermometer = */new KY015()));
    #endif
    #ifdef MHRD
        component_list.push_back(dynamic_cast<Component*>(/*rain_sensor = */new MHRD()));
    #endif
    #ifdef MHRTC2
        component_list.push_back(dynamic_cast<Component*>(/*rtc = */new MHRTC2()));
    #endif
    #ifdef MPL3115A2
        component_list.push_back(dynamic_cast<Component*>(/*barometer = */new MPL3115A2()));
    #endif
    #ifdef ITGMPU6050
        component_list.push_back(dynamic_cast<Component*>(/*gyroscope = */new ITGMPU6050()));
    #endif
    #ifdef ENCODER
        component_list.push_back(dynamic_cast<Component*>(/*speedometer = */new Encoder()));
    #endif
    #ifdef TEMT6000
        component_list.push_back(dynamic_cast<Component*>(/*luxmeter0 = */new TEMT6000()));
    #endif
    #ifdef UV
        component_list.push_back(dynamic_cast<Component*>(/*uv_sensor = */new UV()));
    #endif
}

void setup(){
    Serial.begin(9600);
    while(!Serial);
    newAll();
}

void loop(){
    if(millis()-stopwatch >= READING_DELAY || !stopwatch){
        Serial.println();
        for(auto element : component_list){
            if(element->isStarted()){
                element->read();
                element->print();
                Serial.println();
            }
            else
                element->start();
        }
        stopwatch = millis();
        Serial.println();
    }
}