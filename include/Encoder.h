/* Optical switch encoder speed sensor */

#include "Component.h"

#define ENCODER_PIN 2
#define ENCODER_N 1// Number of encoder interrupts
#define CIRCUNFERENCE_DIAMETER 49// mm

class Encoder : public Component{
    private:
        static bool measure_done;

        static unsigned long T1;
        static unsigned long T2;
        static unsigned long T;

        float info;

        static void INT0_ISR();

    public:
        Encoder();
        ~Encoder();

        float getSpeed() const;

        void print() const override;
        void read() override;
        void start() override;
};