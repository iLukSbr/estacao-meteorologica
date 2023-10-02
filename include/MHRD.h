/* Rain sensor */

#pragma once

#include "Component.h"

#define MHRD_PIN 9

class MHRD : public Component{
    private:
        bool info;

    public:
        MHRD();
        ~MHRD();

        bool getRaining() const;

        void print() const override;
        void read() override;
        void start() override;
};