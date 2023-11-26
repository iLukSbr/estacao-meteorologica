/* SD card reader/writer module */

#include "pch.h"
#include "SDReaderWriter.h"

SDReaderWriter::SDReaderWriter():
    card(new SdFat())
{
    start();
}

SDReaderWriter::~SDReaderWriter(){
    delete card;
}

void SDReaderWriter::print() const{
    
}

void SDReaderWriter::read(){

}

void SDReaderWriter::save(String data){
    SdFile datafile;
    if(!datafile.open(FILENAME, O_RDWR | O_CREAT | O_AT_END))
        Serial.println(F("Error while opening datafile!"));
    else{
        datafile.println(data);
        delay(100);
        datafile.close();
    }
}

void SDReaderWriter::start(){
    Serial.println(F("Starting SD card reader/writer..."));
    SdFile datafile;
    if(!card->begin(CS_PIN, SPI_SPEED))
        Serial.println(F("Error while starting SD card reader/writer."));
    if(!datafile.open(FILENAME, O_RDWR | O_CREAT | O_AT_END))
        Serial.println(F("Error while opening datafile."));
    else{
        started = true;
        delay(100);
        datafile.close();
        Serial.println(F("SD card reader/writer OK!"));
    }
}