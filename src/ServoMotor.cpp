/* Servo Motor */

#include "ServoMotor.h"

ServoMotor::ServoMotor(byte _pin, byte _min_angle, byte _max_angle, byte _count, byte _step):
    count(_count),
    info(0),
    pin(_pin),
    step(constrain(_step, 1, 179)),
    servo(new Servo())
{
    if(_min_angle > _max_angle)
        min_angle = constrain(_max_angle, 0, 180);
    else
        max_angle = constrain(_min_angle, 0, 180);
    if(_max_angle < _min_angle)
        max_angle = constrain(_min_angle, 0, 180);
    else
        min_angle = constrain(_max_angle, 0, 180);
    start();
}

ServoMotor::~ServoMotor(){
    delete servo;
}

byte ServoMotor::getServoAngle() const{
    return info;
}

void ServoMotor::read(){

}

bool ServoMotor::decreaseAngle(){
    if(info > min_angle + step - 1){
        info -= step;
        servo->write(info);
        return true;
    }
    else
        return false;
}

bool ServoMotor::increaseAngle(){
    if(info < max_angle - step + 1){
        info += step;
        servo->write(info);
        return true;
    }
    else
        return false;
}

void ServoMotor::flip(){
    if(info > (max_angle + min_angle)/2)
        info = min_angle + 100 + info;
    else
        info = max_angle - 100 - info;
    servo->write(info);
}

void ServoMotor::print() const{
    // Serial.println("min");
    // for(byte i=0; i<180; i+=20){
    //     servo->write(i);
    //     delay(100);
    // }
    // Serial.println("max");
    Serial.print(F("Servo Motor "));
    Serial.print(count);
    Serial.println(F(":"));
    Serial.print(F("angle = "));
    Serial.print(getServoAngle());
    Serial.println(F("°"));
}

void ServoMotor::start(){
    Serial.print(F("Starting Servo Motor "));
    Serial.print(count);
    Serial.println(F("..."));
    servo->attach(pin);
    info = (min_angle + max_angle)/2;
    servo->write(info);
    started = true;
}

void ServoMotor::unblock(){
    if(info < 90){
        info = 45;
        servo->write(info);
    }
    else{
        info = 135;
        servo->write(info);
    }
}