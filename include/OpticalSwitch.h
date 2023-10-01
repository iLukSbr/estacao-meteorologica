/* Speed sensor */

#define OPTICAL_SWITCH_PIN 8

class OpticalSwitch : public Component{
    private:
        float info;

    public:
        OpticalSwitch();
        ~OpticalSwitch();

        float getSpeed();

        void print() const override;
        void read() override;
        void start() override;
};