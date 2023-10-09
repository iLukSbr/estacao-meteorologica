/* Rain sensor */

#pragma once

#ifndef _MHRD
    #define _MHRD 1
    #define _MHRD_ 1
#endif

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