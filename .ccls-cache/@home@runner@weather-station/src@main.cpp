#include "componentInclude.h"// enable/disable components there

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// GY511* compass1;
// GYNEO6MV2* gps;
// HMC5883L* compass2;
   I2CServoDriver* servo1;
   I2CServoDriver* servo2;
// KY015* thermometer;
  LDR* luxmeter0;
  LDR* luxmeter1;
  LDR* luxmeter2;
  LDR* luxmeter3;
// MHRD* rain_sensor;
// MHRTC2* rtc;
// MPL3115A2* barometer;
// ITGMPU6050* gyroscope;
// Encoder* speedometer;
// TEMT6000* luxmeter0;
// UV* uv_sensor;

unsigned long stopwatch = 0;

Component* storage_array[QUANTITY_OF_COMPONENTS] = {nullptr};
Vector<Component*> component_list(storage_array);

void newAll(){
    #ifdef _GY511
        component_list.push_back(dynamic_cast<Component*>(/*compass1 = */new GY511()));
    #endif
    #ifdef _GYNEO6MV2
        component_list.push_back(dynamic_cast<Component*>(/*gps = */new GYNEO6MV2()));
    #endif
    #ifdef _HMC5883L
        component_list.push_back(dynamic_cast<Component*>(/*compass2 = */new HMC5883L()));
    #endif
    #ifdef _I2CSERVODRIVER
        component_list.push_back(dynamic_cast<Component*>(servo1 = new I2CServoDriver(15, 150, 420, 0)));
        component_list.push_back(dynamic_cast<Component*>(servo2 = new I2CServoDriver(14, 99, 456, 0)));
    #endif
    #ifdef _LDR
        component_list.push_back(dynamic_cast<Component*>(luxmeter0 = new LDR(A0)));  
        component_list.push_back(dynamic_cast<Component*>(luxmeter1 = new LDR(A1)));
        component_list.push_back(dynamic_cast<Component*>(luxmeter2 = new LDR(A2)));
        component_list.push_back(dynamic_cast<Component*>(luxmeter3 = new LDR(A3)));
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
    #ifdef _ITGMPU6050
        component_list.push_back(dynamic_cast<Component*>(/*gyroscope = */new ITGMPU6050()));
    #endif
    #ifdef _ENCODER
        component_list.push_back(dynamic_cast<Component*>(/*speedometer = */new Encoder()));
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
                Serial.println();
                element->print();
                Serial.println();
            }
        }
        else
            element->start();
    }
    Serial.println();
}