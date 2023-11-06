#include <Wire.h>

// #include "ArduinoUnoTX.h"// SLAVE, enable for slave, disable for main
#include "ArduinoUnoRX.h"// MAIN, enable for main, disable for slave
#include "componentInclude.h"// enable/disable components there

#define JSON_DELAY 60000// ms

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// Encoder* speedometer;
#ifdef UNO_MAIN
    ESP01* wifi;
    ArduinoUnoRX* uno;
#elif defined(UNO_SLAVE)
    ArduinoUnoTX* uno;
#endif
// GYNEO6MV2* gps;
// KY015* thermometer;
// KY021* rain_gauge;
// KY36* led;
// MHRTC2* rtc;
SDReaderWriter* micro_sd;
// MPL3115A2* barometer;
Relay* relay;
// SolarTracker* solar_tracker;
// TEMT6000* luxmeter0;
// UV* uv_sensor;

unsigned long stopwatch = 0;

Component* storage_array[QUANTITY_OF_COMPONENTS] = {nullptr};
Vector<Component*> component_list(storage_array);

void beginI2C(){
    #ifdef UNO_MAIN
        Wire.begin(MAIN_UNO_I2C_ADDRESS);
    #elif defined(UNO_SLAVE)
        Wire.begin(SLAVE_UNO_I2C_ADDRESS);
    #else
        Wire.begin();
    #endif
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

char* makeJSON(){
    StaticJsonDocument<1000> doc;
    char* doc_serialized;
    for(auto element : component_list){
        if(element->isStarted()){
            element->makeJSON(doc);
        }
    }
    #ifdef UNO_MAIN
        uno->receive();
        char* slave_doc_serialized = uno->getData();
        deserializeJson(slave_doc, slave_doc_serialized);
        merge(doc, slave_doc);
    #endif
    serializeJson(doc, doc_serialized);
    return doc_serialized;
}

void merge(JsonObject dest, JsonObjectConst src)
{
    for(JsonPairConst kvp : src)
        dest[kvp.key()] = kvp.value();
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
    if(millis() - stopwatch > JSON_DELAY || !stopwatch){
        char* json_str = makeJSON();
        micro_sd->save(json_str);
        #ifdef UNO_MAIN
            wifi->send(json_str);
        #elif defined(UNO_SLAVE)
            uno->send(json_str);
        #endif
        Serial.println(json_str);
        Serial.println();
        stopwatch = millis();
    }
    delay(10);
}