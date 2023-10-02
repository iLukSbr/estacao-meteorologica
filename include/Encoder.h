/* Optical switch encoder speed sensor */

#include "Component.h"

#define ENCODER_PIN 2
#define ENCODER_N 1// Number of encoder interrupts
#define CIRCUNFERENCE_DIAMETER 49// mm

class Encoder : public Component{
    private:
        static volatile byte pulses;

        float info;

        unsigned long timeold;
        unsigned long rpm;

    public:
        Encoder();
        ~Encoder();

        float getSpeed() const;

        void print() const override;
        void read() override;
        void start() override;
        static void counter();
};