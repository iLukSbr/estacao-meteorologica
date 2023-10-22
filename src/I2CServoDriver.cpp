#include "I2CServoDriver.h"

Adafruit_PWMServoDriver* I2CServoDriver::pwm = new Adafruit_PWMServoDriver();

I2CServoDriver::I2CServoDriver(byte _pin, unsigned short _min_freq, unsigned short _max_freq, byte _count, unsigned short _step):
    count(_count),
    pin(_pin),
    min_freq(_min_freq),
    max_freq(_max_freq),
    step(_step)
{
    info = (min_freq + max_freq)/2;
    start();
}

I2CServoDriver::~I2CServoDriver(){

}

unsigned short I2CServoDriver::getServoPWM() const{
    return info;
}

void I2CServoDriver::read(){

}

bool I2CServoDriver::decreasePWM(){
    if(info > min_freq + step - 1){
        pwm->setPWM(pin, 0, info-=step);
        return true;
    }
    else
        return false;
}

bool I2CServoDriver::increasePWM(){
    if(info < max_freq - step + 1){
        pwm->setPWM(pin, 0, info+=step);
        return true;
    }
    else
        return false;
}

void I2CServoDriver::flip(){
    if(info > (max_freq + min_freq)/2)
        info = min_freq + info;
    else
        info = max_freq - info;
    pwm->setPWM(pin, 0, info);
}

void I2CServoDriver::print() const{
    Serial.println(F("I²C Servo Driver:"));
    Serial.print(F("servo"));
    Serial.print(count);
    Serial.print(F(" pwm = "));
    Serial.print(getServoPWM());
    Serial.println(F(" Hz"));
}

void I2CServoDriver::start(){
    Serial.print(F("Starting I²C Servo Driver"));
    Serial.print(count);
    Serial.println(F("..."));
    if(count == 1){
        pwm->begin();
        pwm->setOscillatorFrequency(OSCILLATOR_FREQ);
        pwm->setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    }
    started = true;
}