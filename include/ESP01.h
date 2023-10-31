/* ESP-01 Wi-Fi module */

#pragma once

#include "Component.h"

#ifndef _ESP_01
    #define _ESP_01
    #define _ESP_01_ 1
#endif

class ESP01 : public Component{
    private:

    public:
        ESP01();
        ~ESP01();

        void print() const override;
        void read() override;
        void start() override;    
}