/* Taidacent UV sensor */

#pragma once

#ifndef _UV
    #define _UV
    #define _UV_ 1
#endif

#include "Component.h"

#define UV_PIN A4
#define UV_MEASURES 255
#define UV_INDEX_KEY "indiceUV"

class UV : public Component{
    private: 
        byte info;

    public:
        UV();
        ~UV();

        byte getUVIndex() const;

        void makeJson(JsonDocument& doc) override;
        void print() const override;
        void read() override;
        void start() override;
};