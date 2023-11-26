/* SD card reader/writer module */

#pragma once

#include <SdFat.h>

#include "Component.h"

#ifndef _MICROSD_READER_WRITER
    #define _MICROSD_READER_WRITER
#endif

#define CS_PIN 5
#define FILENAME "weather_station.json"
#define SPI_SPEED 9600// Hz

class SDReaderWriter : public Component{
    private:
        SdFat* card;

    public:
        SDReaderWriter();
        ~SDReaderWriter();

        void print() const override;
        void read() override;
        void save(String data);
        void start() override;
};