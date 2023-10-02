/* Optical switch encoder speed sensor */

#include "Component.h"

#define ENCODER_PIN 2
#define ENCODER_N 1// Number of encoder interrupts
#define CIRCUNFERENCE_DIAMETER 49// mm

class Encoder : public Component{
    private:
        bool measure_done;

        unsigned long T1;
        unsigned long T2;
        unsigned long T;

        float info;

        void INT0_ISR();

    public:
        Encoder();
        ~Encoder();

        float getSpeed();

        void print() const override;
        void read() override;
        void start() override;
};