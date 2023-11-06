/* ESP-01 Wi-Fi module */

#pragma once

#include "Component.h"

class ESP01 : public Component{
    private:

    public:
        ESP01();
        ~ESP01();

        void print() const override;
        void read() override;
        void send(char* data);
        void start() override;    
};