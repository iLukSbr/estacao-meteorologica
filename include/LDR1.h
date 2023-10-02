/* LDR luminosity sensor */

#include "Component.h"

#define LDR1_PIN A2
#define LDR1_RESISTOR 10000

class LDR1 : public Component{
    private: 
        float info;

    public:
        LDR1();
        ~LDR1();

        float getIlluminance() const;

        void print() const override;
        void read() override;
        void start() override;
};