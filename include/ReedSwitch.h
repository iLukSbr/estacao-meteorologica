/* Reed switch only */

#pragma once

#include <Mux.h>

#include "Component.h"

using namespace admux;

class ReedSwitch : public Component{
    private:
        bool info;

        byte pin;

    public:
        ReedSwitch(byte _pin);
        ~ReedSwitch();

        void getState() const;
        void print() const override;
        void read() override;
        void start() override;
}