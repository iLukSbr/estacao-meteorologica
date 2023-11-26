#include "pch.h"

#include <Wire.h>

#include "componentInclude.h"// enable/disable components there

#define MAKE_JSON
#define SEND_JSON_DELAY 10000// ms
#define TIME_KEY "dataHora"

/* Specific pointers to access exclusive methods of the component
    Uncomment here and in newAll() if necessary
    Comment here and in newAll() if not necessary */
// Encoder* speedometer;
ESP01* wifi = new ESP01();
// GYNEO6MV2* gps;
// INA219 *multimeter_solar, *multimeter_batteries;
// KY015* thermometer;
// KY021* rain_gauge;
// MHRD* rain_sensor;
// MHRTC2* rtc = new MHRTC2();
// MPL3115A2* barometer;
#ifdef _RELAY
    Relay* relay = new Relay();
#endif
#ifdef _MICROSD_READER_WRITER
    SDReaderWriter* sd = new SDReaderWriter();
#endif
// SolarTracker* solar_tracker;
// TEMT6000* luxmeter0;
#ifdef _TTP223B
    TTP223B* led = new TTP223B();
#endif
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
        delay(100);
    #endif
    #ifdef _GYNEO6MV2
        component_list.push_back(dynamic_cast<Component*>(/*gps = */new GYNEO6MV2()));
        delay(100);
    #endif
    #ifdef _INA219
        // component_list.push_back(dynamic_cast<Component*>(/*multimeter_solar = */new INA219(0x40, 0, PG_80, BRNG_16, 1.f, 1.f)));
        delay(100);
        // component_list.push_back(dynamic_cast<Component*>(/*multimeter_batteries = */new INA219(0x41, 1, PG_160, BRNG_32, 1.f, 1.f)));
        delay(100);
    #endif
    #ifdef _KY015
        component_list.push_back(dynamic_cast<Component*>(/*thermometer = */new KY015()));
        delay(100);
    #endif
    #ifdef _KY021
        component_list.push_back(dynamic_cast<Component*>(/*rain_gauge = */new KY021()));
        delay(100);
    #endif
    #ifdef _MHRD
        component_list.push_back(dynamic_cast<Component*>(/*rain_sensor = */new MHRD()));
        delay(100);
    #endif
    #ifdef _MPL3115A2
        component_list.push_back(dynamic_cast<Component*>(/*barometer = */new MPL3115A2()));
        delay(100);
    #endif
    #ifdef _SOLAR_TRACKER
        component_list.push_back(dynamic_cast<Component*>(/*solar_tracker = */new SolarTracker()));
        delay(100);
    #endif
    #ifdef _TEMT6000
        component_list.push_back(dynamic_cast<Component*>(/*luxmeter0 = */new TEMT6000()));
        delay(100);
    #endif
    #ifdef _UV
        component_list.push_back(dynamic_cast<Component*>(/*uv_sensor = */new UV()));
        delay(100);
    #endif
}

#ifdef MAKE_JSON
    void sendJson(){
        StaticJsonDocument<384> doc;
        doc[F("latitude")] = 9;
        doc[F("longitude")] = 9;
        doc[F("altitude")] = 9;
        doc[F("temperatura")] = 9;
        doc[F("pressao")] = 9;
        doc[F("umidade")] = 9;
        doc[F("velocidadeVento")] = 9;
        doc[F("direcaoVento")] = "S";
        doc[F("indiceUV")] = 9;
        doc[F("intensidadeLuminosa")] = 9;
        doc[F("chuva")] = true;
        doc[F("volumeChuva")] = 9;
        doc[F("porcentagemBaterias")] = 9;
        doc[F("tensaoEletricaPlacaSolar")] = 9;
        doc[F("orientacaoPlacaSolar")] = "S";
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
        for(auto element : component_list)
            if(element->isStarted())
                element->makeJson(doc);
        int tamdoc = measureJson(doc);
        Serial.println();
        Serial.print(F("Tamanho do json = "));
        Serial.println(tamdoc);

    if (wifi->sendCommand("AT+CIPSTART=\"SSL\",\"api-oficinas.onrender.com\",443", 1, "OK")) {
        String tam = String(139 + tamdoc);
        String cipSend = "AT+CIPSEND=";
        cipSend += tam;
        wifi->sendCommand(cipSend, 1, ">");
        delay(500);
        wifi->sendData(tamdoc, doc);
        delay(500);
    }

    wifi->sendCommand("AT+CIPCLOSE", 1, "OK");
        #ifdef _MHRTC2
            rtc->read();
            doc[F(TIME_KEY)] = rtc->getDateTime();
        #endif
    doc.clear();
}
#endif

void setup(){
    Serial.begin(9600);
    while(!Serial){}
    delay(100);
    #ifdef _RELAY
        relay->on();
        relay->print();
    #endif
    delay(100);
    newAll();
}

void loop(){
    #ifdef MAKE_JSON
        if(millis() - stopwatch > SEND_JSON_DELAY || !stopwatch){
            delay(100);
            sendJson();
            delay(100);
            #ifdef _MICROSD_READER_WRITER
                // sd->save(json_str);
            #endif
            // Serial.println(json_str);
            // Serial.println();
            stopwatch = millis();
        }
    #endif
    // delay(30000);
}