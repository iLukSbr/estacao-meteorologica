#include "I2CServoDriver.h"

I2CServoDriver::I2CServoDriver():
    pwm(new Adafruit_PWMServoDriver())
{
    start();
}

I2CServoDriver::~I2CServoDriver(){
    delete pwm;
}

float I2CServoDriver::getPotentiometerRead() const{
    return info[0]*5.f/1024.f;
}

long I2CServoDriver::getServoPWM() const{
    return info[1];
}

void I2CServoDriver::read(){
    info[0] = analogRead(POTENTIOMETER_PIN);
    info[1] = map(info[0], 0, 1023, SERVO_SOLAR_MIN, SERVO_SOLAR_MAX);
    pwm->setPWM(SERVO_SOLAR_PIN, 0, info[1]);
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