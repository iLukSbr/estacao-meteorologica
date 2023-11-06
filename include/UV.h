/* Taidacent UV sensor */

#pragma once

#ifndef _UV
    #define _UV
    #define _UV_ 1
#endif

#include "Component.h"

#define UV_PIN A1
#define UV_MEASURES 256

class UV : public Component{
    private: 
        byte info;

    public:
        UV();
        ~UV();

        byte getUVIndex() const;

        void print() const override;
        void read() override;
        void start() override;
};