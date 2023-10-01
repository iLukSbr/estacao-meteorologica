/* Taidacent UV sensor */

#include "uv.h"

UV::UV():
    info(0)
{
    start();
}

UV::~UV(){

}

byte getUVIndex() const{
    return info;
}

void UV::print() const{
    Serial.println(F("UV:"));
    Serial.println(F("Índice UV:"));
    Serial.println(info);
}

void UV::read(){
    info = map(analogRead(UV_PIN), 0, 203, 0, 10); // CONVERTE A FAIXA DE SINAL DO SENSOR DE 0V A 1V PARA O INDICE UV DE 0 A 10.
}

void UV::start(){
    pinMode(UV_PIN, INPUT);
    started = true;
}