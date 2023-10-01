/* Magnetometer compass and accelerometer */

class GY511 : public Component{
    private:
        info[6];
    
    public:
        GY511();
        ~GY511();
        
        void print() const override;
        void read() override;
        void start() override;
};