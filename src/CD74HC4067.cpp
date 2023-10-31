/* 16 channel demultimplexer CD74HC4067 */

#include "CD74HC4067.h"

CD74HC4067::CD74HC4067(){
    start();
}

CD74HC4067::~CD74HC4067(){
    
}

void CD74HC4067::getState() const{
    
}

void CD74HC4067::start(){
    for(int i=0; i<16; i++){
        switches[i] = new ReedSwitch(i);
    }
}