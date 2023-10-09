#include "I2CServoDriver.h"

I2CServoDriver::I2CServoDriver(byte _pin, unsigned short _min_freq, unsigned short _max_freq, unsigned long _measure_delay = 10):
    pwm(new Adafruit_PWMServoDriver()),
    pin(_pin),
    min_freq(_min_freq),
    max_freq(_max_freq)
{
    info[1] = (min_freq + max_freq)/2;
    measure_delay = _measure_delay;
    start();
}

I2CServoDriver::~I2CServoDriver(){

}

float I2CServoDriver::getPotentiometerRead() const{
    return info[0]*5.f/1024.f;
}

long I2CServoDriver::getServoPWM() const{
    return info[1];
}

void I2CServoDriver::read(){
    info[0] = analogRead(POTENTIOMETER_PIN);
    long read = map(info[0], 0, 1023, min_freq, max_freq);
    if(read > info[1])
        pwm->setPWM(pin, 0, ++info[1]);
    else if(read < info[1])
        pwm->setPWM(pin, 0, --info[1]);
}

bool I2CServoDriver::turnLeft(){
    if(info[1] < max_freq){
        pwm->setPWM(pin, 0, ++info[1]);
        return true;
    else
        return false;
}

bool I2CServoDriver::turnRight(){
    if(info[1] > min_freq){
        pwm->setPWM(pin, 0, --info[1]);
        return true;
    }
    else
        return false;
}

void I2CServoDriver::print() const{
    Serial.println(F("I²C Servo Driver:"));
    Serial.print(F("potentiometer read = "));
    Serial.print(getPotentiometerRead());
    Serial.println(F(" V"));
    Serial.print(F("servo pwm = "));
    Serial.print(getServoPWM());
    Serial.println(F(" Hz"));
}

void I2CServoDriver::start(){
    pwm->begin();
    pwm->setOscillatorFrequency(OSCILLATOR_FREQ);
    pwm->setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    pinMode(POTENTIOMETER_PIN, INPUT);
    started = true;
}