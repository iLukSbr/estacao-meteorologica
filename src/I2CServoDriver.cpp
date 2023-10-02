#include "I2CServoDriver.h"

I2CServoDriver::I2CServoDriver():
    pwm(new Adafruit_PWMServoDriver())
{
    start();
}

I2CServoDriver::~I2CServoDriver(){
    delete pwm;
}

long I2CServoDriver::getPotentiometerRead() const{
    return info[0];
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
    Serial.println(F("Servos: "));
    Serial.print(F("potentiometer read = "));
    Serial.println(getPotentiometerRead());
    Serial.print(F("servo pwm = "));
    Serial.println(getServoPWM());
}

void I2CServoDriver::start(){
    pwm->begin();
    pwm->setOscillatorFrequency(OSCILLATOR_FREQ);
    pwm->setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
    pinMode(POTENTIOMETER_PIN, INPUT);
    started = true;
}