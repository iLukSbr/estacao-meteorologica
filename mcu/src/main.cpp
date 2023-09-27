#include <Vector.h>

#include "KY015.h"
#include "MPL3115A2.h"

#define QUANTITY_OF_COMPONENTS 2
#define READING_DELAY 3000// (ms) Delay between readings

unsigned long stopwatch = 0;

MPL3115A2* barometer;
KY015* thermometer;

Component* storage_array[QUANTITY_OF_COMPONENTS] = {nullptr};
Vector<Component*> component_list(storage_array);

void newAll(){
    component_list.push_back(dynamic_cast<Component*>(barometer = new MPL3115A2()));
    component_list.push_back(dynamic_cast<Component*>(thermometer = new KY015()));
}

void setup(){
    Serial.begin(115200);
    while(!Serial);
    newAll();
}

void loop(){
    if(millis()-stopwatch >= READING_DELAY || !stopwatch){
        for(auto element : component_list){
            if(element->isStarted()){
                element->read();
                element->print();
            }
            else
                element->start();
        }
        stopwatch = millis();
        Serial.println();
    }
}