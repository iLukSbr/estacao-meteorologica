/* 16 channel demultimplexer CD74HC4067 */

class CD74HC4067 : public Component{
    private:
        ReedSwitch* switches[16];

        char* info[4];

    public:
        CD74HC4067();
        ~CD74HC4067();

        void getState() const;
        void print() const override;
        void read() override;
        void start() override;
}