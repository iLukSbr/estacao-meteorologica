/* SD card reader/writer module */

#pragma once

#include <SdFat.h>

#include "Component.h"

#ifndef _SD_READER_WRITER
    #define _SD_READER_WRITER
    #define _SD_READER_WRITER_ 1
#endif

#define CS_PIN 5
#define FILENAME weather_station.json

class SDReaderWriter : public Component{
    private:
        SdFat* card;
        
        SdFile* datafile;

    public:
        SDReaderWriter();
        ~SDReaderWriter();

        void print() const override;
        void read() override;
        void save(char* data);
        void start() override;
}