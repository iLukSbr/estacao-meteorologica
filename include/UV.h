/* Taidacent UV sensor */

#pragma once

#include "Component.h"

#define UV_PIN A1

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