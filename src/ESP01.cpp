/* ESP-01 Wi-Fi module */

#include "pch.h"
#include "ESP01.h"

ESP01::ESP01(){

}

ESP01::~ESP01(){

}

void ESP01::print() const{
    
}

void ESP01::read(){

}

void ESP01::send(char* data){
    
}

void ESP01::start(){

}

// #include <SoftwareSerial.h>
// #include <ArduinoJson.h>

// class SensorData {
// public:
//   int latitude;
//   int longitude;
//   int altitude;
//   int temperatura;
//   int pressao;
//   int umidade;
//   int velocidadeVento;
//   const char* direcaoVento;
//   int indiceUV;
//   int intensidadeLuminosa;
//   bool chuva;
//   int volumeChuva;
//   int porcentagemBaterias;
//   int tensaoEletricaPlacaSolar;
//   const char* orientacaoPlacaSolar;

//   SensorData() : latitude(2), longitude(2), altitude(2), temperatura(2), pressao(2), umidade(2),
//                 velocidadeVento(2), direcaoVento("N"), indiceUV(2), intensidadeLuminosa(2),
//                 chuva(true), volumeChuva(2), porcentagemBaterias(2),
//                 tensaoEletricaPlacaSolar(2), orientacaoPlacaSolar("N") {}
// };

// class ESP8266Communication {
// private:
//   SoftwareSerial esp8266;
//   int countTrueCommand;
//   int countTimeCommand;
//   bool found;

// public:
//   ESP8266Communication(int rxPin, int txPin) : esp8266(rxPin, txPin), countTrueCommand(0), countTimeCommand(0), found(false) {}
//   //Manda os comandos no serial do RX|TX
//   bool sendCommand(String command, int maxTime, String readReplay) {
//     /*---------------------SERIAL PRINT-----------------
//     Serial.print(countTrueCommand);
//     Serial.print(". at command => ");
//     Serial.print(command);
//     Serial.print(" ");
//     ----------------------------------------------------*/
//     char finde[readReplay.length()];
//     readReplay.toCharArray(finde, readReplay.length());

//     while (countTimeCommand < (maxTime * 1)) {
//       esp8266.println(command);
//       delay(500);

//       if (esp8266.find(finde)) {
//         found = true;
//         break;
//       }
//       countTimeCommand++;
//     }
//     if (found == true) {
//       Serial.println("Success");
//       countTrueCommand++;
//       countTimeCommand = 0;
//       found = false;
//       return true;
//     }

//     if (found == false) {
//       Serial.println("Fail");
//       countTrueCommand = 0;
//       countTimeCommand = 0;
//       return false;
//     }

//     found = false;
//   }

//   void begin(int baudRate) {
//     esp8266.begin(baudRate);
//     esp8266.print("AT+UART_CUR=9600,8,1,0,0\r\n");
//     esp8266.begin(baudRate);
//   }

//   void sendData(String host, String path, int port, int tamdoc, StaticJsonDocument<384>& doc) {
//     int delayp = 200;
//     /*   SERIAL PRINT

//     Serial.println(F("POST /sensores HTTP/1.1"));
//     Serial.println(F("Host: api-oficinas.onrender.com"));
//     //Serial.println(F("Connection: keep-alive"));//22
//     Serial.println(F("Accept: application/json"));
//     Serial.println(F("Content-Type: application/json"));
//     Serial.print(F("Content-Length: "));
//     Serial.println(String(tamdoc));
//     Serial.println();
//     */
    
//     esp8266.println(F("POST /sensores HTTP/1.1"));
//     delay(delayp);
//     esp8266.println(F("Host: api-oficinas.onrender.com"));
//     delay(delayp);

//     /* KEEP ALIVE
//     //esp8266.println(F("Connection: keep-alive"));
//     //delay(delayp);*/
    

//     /* ---------------------- PRINT SERIAL RX|TX------------------------------------------*/
//     esp8266.println(F("Accept: application/json"));
//     delay(delayp);
//     esp8266.println(F("Content-Type: application/json"));
//     delay(delayp); 
//     esp8266.print(F("Content-Length: "));
//     esp8266.println(String(tamdoc));
//     delay(delayp);
//     esp8266.println();
//     delay(delayp); 
//     serializeJson(doc,Serial);
//     serializeJson(doc,esp8266);
//     delay(delayp); 
//     // PRINT RESPOSTA
//     //printResponse();
//     delay(5000);
//     countTrueCommand++;
//   }

//   void printResponse() {
//     while (esp8266.available()) {
//       Serial.println();
//       String tmpResp = esp8266.readString();
//       Serial.println(tmpResp);
//     }
//   }
// };

// void setup() {
//   SensorData sensorData;
//   ESP8266Communication espCommunication(2, 3);
//   StaticJsonDocument<384> doc;
//   espCommunication.begin(115200);
//   /* Additional setup code if needed*/
// }

// void loop() {
//   SensorData sensorData;
//   ESP8266Communication espCommunication(2, 3);

//   // Update sensor data as needed

  
//   doc["latitude"] = sensorData.latitude;
//   doc["longitude"] = sensorData.longitude;
//   // Add other sensor data fields

//   int tamdoc = measureJson(doc);

//   if (espCommunication.sendCommand("AT+CIPSTART=\"SSL\",\"api-oficinas.onrender.com\",443", 1, "OK")) {
//     String tam = String(139 + tamdoc);
//     String cipSend = "AT+CIPSEND=";
//     cipSend += tam;
//     espCommunication.sendCommand(cipSend, 1, ">");
//     delay(500);
//     espCommunication.sendData("api-oficinas.onrender.com", "/sensores", 443, tamdoc, doc);
//     delay(500);
//   }

//   espCommunication.sendCommand("AT+CIPCLOSE", 1, "OK");
//   delay(10000); // Adjust delay as needed
// }