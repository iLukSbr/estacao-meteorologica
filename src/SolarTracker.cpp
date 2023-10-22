/* Solar Tracker */
/* P.S. This start() has do...while and read() has !gyro->isMoving() blocking */

#include "SolarTracker.h"

SolarTracker::SolarTracker():
    light_change_detected(false)
{
    start();
}

SolarTracker::~SolarTracker(){
    
}

void SolarTracker::checkLightChange(){
    float mean1_2 = (ldr1->getIlluminance() + ldr2->getIlluminance())/2;
    float mean3_4 = (ldr3->getIlluminance() + ldr4->getIlluminance())/2;
    float mean1_4 = (ldr1->getIlluminance() + ldr4->getIlluminance())/2;
    float mean2_3 = (ldr2->getIlluminance() + ldr3->getIlluminance())/2;
    float dif_x = mean1_4 - mean2_3;
    float dif_y = mean1_2 - mean3_4;
    light_change_detected = false;
    if(-TOLERANCE > dif_x || dif_x > TOLERANCE){
        lightChangeDetected();
        if(servo_panel->getServoAngle() < 90){
            if(mean1_4 > mean2_3 && !servo_base->decreaseAngle()){
                flip();
            }
            else if(mean2_3 > mean1_4 && !servo_base->increaseAngle()){
                flip();
            }
        }
        else{
            if(mean1_4 > mean2_3 && !servo_base->increaseAngle()){
                flip();
            }
            else if(mean2_3 > mean1_4 && !servo_base->decreaseAngle()){
                flip();
            }
        }            
    }
    if(-TOLERANCE > dif_y || dif_y > TOLERANCE){
        lightChangeDetected();
        if(mean1_2 > mean3_4)
            servo_panel->increaseAngle();
        else if(mean1_2 < mean3_4)
            servo_panel->decreaseAngle();
    }
}

void SolarTracker::checkServosMovement(){
    gyro->read();
    if(!gyro->isMoving()){
        Serial.println(F("A servo motor is blocked!"));
        unblock();
    }
}

void SolarTracker::flip(){
    servo_base->flip();
    servo_panel->flip();
}

void SolarTracker::lightChangeDetected(){
    Serial.println(F("Light change detected!"));
    light_change_detected = true;
}

void SolarTracker::print() const{
    gyro->read();
    ldr1->read();
    ldr2->read();
    ldr3->read();
    ldr4->read();
    servo_base->print();
    servo_panel->print();
    ldr1->print();
    ldr2->print();
    ldr3->print();
    ldr4->print();
    servo_base->print();
    servo_panel->print();
    gyro->print();
}

void SolarTracker::read(){
    gyro->read();
    ldr1->read();
    ldr2->read();
    ldr3->read();
    ldr4->read();
    checkLightChange();
    if(light_change_detected)
        checkServosMovement();
}

void SolarTracker::start(){
    Serial.println(F("Starting Solar Tracker..."));
    do{
        servo_base = new ServoMotor(SERVO_BASE_PIN, SERVO_BASE_MIN, SERVO_BASE_MAX, 1, SERVO_BASE_STEP);
        delay(10);
    }while(!servo_base->isStarted());
    do{
        servo_panel = new ServoMotor(SERVO_PANEL_PIN, SERVO_PANEL_MIN, SERVO_PANEL_MAX, 2, SERVO_PANEL_STEP);
    }while(!servo_base->isStarted());
    ldr1 = new LDR(LDR1_PIN, 1, LDR1_RESISTOR);
    ldr2 = new LDR(LDR2_PIN, 2, LDR2_RESISTOR);
    ldr3 = new LDR(LDR3_PIN, 3, LDR3_RESISTOR);
    ldr4 = new LDR(LDR4_PIN, 4, LDR4_RESISTOR);
    delay(3000);
    do{
        gyro = new ITGMPU6050();
        delay(10);
    }while(!gyro->isStarted());
    started = true;
}