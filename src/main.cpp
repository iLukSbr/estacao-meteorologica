#include <Vector.h>

#include "KY015.h"
#include "MPL3115A2.h"

#define QUANTITY_OF_COMPONENTS 2
#define READING_DELAY 3000// (ms) Delay between readings

unsigned long stopwatch = 0;

GY511* compass1;
KY015* thermometer;
MPL3115A2* barometer;
UV* uv_sensor;


Component* storage_array[QUANTITY_OF_COMPONENTS] = {nullptr};
Vector<Component*> component_list(storage_array);

void newAll(){
    component_list.push_back(dynamic_cast<Component*>(compass1 = new GY511()));
    component_list.push_back(dynamic_cast<Component*>(thermometer = new KY015()));
    component_list.push_back(dynamic_cast<Component*>(barometer = new MPL3115A2()));
    component_list.push_back(dynamic_cast<Component*>(uv_sensor = new UV()));
}

void setup(){
    Serial.begin(115200);
    while(!Serial);
    newAll();
}

void loop(){
    if(millis()-stopwatch >= READING_DELAY || !stopwatch){
        Serial.println(F("========================================"));
        for(auto element : component_list){
            if(element->isStarted()){
                element->read();
                element->print();
                Serial.println(F("========================================"));
            }
            else
                element->start();
        }
        stopwatch = millis();
        Serial.println();
    }
}