/* SD card reader/writer module */

#include "SDReaderWriter.h"

SDReaderWriter::SDReaderWriter(){
    start();
}

SDReaderWriter::~SDReaderWriter(){
    delete card;
    delete datafile;
}

void SDReaderWriter::print() const{
    
}

void SDReaderWriter::read(){

}

void SDReaderWriter::save(char* data){
    if(!datafile.open(F(FILENAME), O_RDWR | O_CREAT | O_AT_END))
        datafile->errorHalt(F("Error while opening datafile!"));
    else{
        datafile->println(data);
        datafile->close();
    }
}

void SDReaderWriter::start(){
    if(!card->begin(CS_PIN, SPI_HALF_SPEED))
        card->initErrorHalt();
    if(!datafile.open(F(FILENAME), O_RDWR | O_CREAT | O_AT_END))
        datafile->errorHalt(F("Error while opening datafile!"));
    else{
        started = true;
        datafile->close();
    }
}