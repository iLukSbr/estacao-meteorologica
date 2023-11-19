/* Taidacent UV sensor */

#include "uv.h"

UV::UV():
    info(0)
{
    start();
}

UV::~UV(){

}

byte UV::getUVIndex() const{
    return info;
}

void UV::print() const{
    Serial.println(F("Taidacent UV:"));
    Serial.print(F("UV index = "));
    Serial.println(info);
}

void UV::read(){
    info = constrain(map(analogRead(UV_PIN), 0, 203, 0, 10), 0, 11); // CONVERTE A FAIXA DE SINAL DO SENSOR DE 0V A 1V PARA O INDICE UV DE 0 A 11.
}

void UV::start(){
    pinMode(UV_PIN, INPUT);
    started = true;
}


void UV::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F("indiceUV")] = getUVIndex();
}