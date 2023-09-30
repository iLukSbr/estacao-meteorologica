#include <Arduino.h>
#include "UVHandler.h"

UVHandler::UVHandler(int pinSensorUV) : pinSensorUV(pinSensorUV) {
  leituraUV=0; // VARIÁVEL PARA ARMAZENAR A LEITURA DA PORTA ANALÓGICA
  indiceUV=0;  // VARIÁVEL PARA ARMAZENAR A CONVERSÃO PARA INDICE UV
}

void UVHandler::begin(){
  Serial.begin(UV_Serial); 
  pinMode(pinSensorUV, OUTPUT);
}

void UVHandler::printUV() {
  delay(500); // DELAY PARA APROXIMAR AS MEDIDAS DO TEMPO DE RESPOSTA DO SENSOR DE 500 mS
  
  leituraUV = analogRead(pinSensorUV); // REALIZA A LEITURA DA PORTA ANALÓGICA 
  indiceUV = map(leituraUV, 0,203,0,10) ; // CONVERTE A FAIXA DE SINAL DO SENSOR DE 0V A 1V PARA O INDICE UV DE 0 A 10.

  Serial.print("Indice UV: ");
  Serial.println(indiceUV);
}