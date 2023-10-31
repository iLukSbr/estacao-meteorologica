/* SD card reader/writer module */

#pragma once

#include <SdFat.h>

#include "Component.h"

#ifndef _SD_READER_WRITER
    #define _SD_READER_WRITER
    #define _SD_READER_WRITER_ 1
#endif

class SDReaderWriter : public Component{
    private:

    public:
        SDReaderWriter();
        ~SDReaderWriter();

        void print() const override;
        void read() override;
        void start() override;    
}