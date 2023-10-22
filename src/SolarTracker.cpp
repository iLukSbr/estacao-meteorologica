/* Solar Tracker */
/* P.S. This start() has do...while and read() has !gyro->isMoving() blocking */

#include "SolarTracker.h"

SolarTracker::SolarTracker():
    light_change_detected(false)
{
    // measure_delay = 10;
    start();
}

SolarTracker::~SolarTracker(){
    
}

void SolarTracker::checkLightChange(){
    if(ldr1->getIlluminance() > ldr2->getIlluminance() + TOLERANCE && ldr4->getIlluminance() > ldr3->getIlluminance() + TOLERANCE){
        lightChangeDetected();
        if(!servo_base->decreasePWM())
            flip();
    }
    else if(ldr1->getIlluminance() + TOLERANCE < ldr2->getIlluminance() && ldr4->getIlluminance() + TOLERANCE < ldr3->getIlluminance()){
        lightChangeDetected();
        if(!servo_base->increasePWM())
            flip();
    }
    else
        light_change_detected = false;
    if(ldr1->getIlluminance() > ldr4->getIlluminance() + TOLERANCE && ldr2->getIlluminance() > ldr3->getIlluminance() + TOLERANCE){
        lightChangeDetected();
        servo_panel->decreasePWM();
    }
    else if(ldr1->getIlluminance() + TOLERANCE < ldr4->getIlluminance() && ldr2->getIlluminance() + TOLERANCE < ldr3->getIlluminance()){
        lightChangeDetected();
        servo_panel->increasePWM();
    }
    else
        light_change_detected = false;
}

void SolarTracker::checkServosMovement(){
    gyro->read();
    if(light_change_detected && !gyro->isMoving()){
        Serial.println(F("A servo motor is blocked!"));
        unblockServos();
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
    checkServosMovement();
}

void SolarTracker::start(){
    Serial.println(F("Starting Solar Tracker..."));
    do{
        servo_base = new I2CServoDriver(SERVO_BASE_PIN, PWM_MIN, PWM_MAX, 1);
        delay(10);
    }while(!servo_base->isStarted());
    do{
        servo_panel = new I2CServoDriver(SERVO_PANEL_PIN, PWM_MIN, PWM_MAX, 2);
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

void SolarTracker::unblockServos(){
    byte i;
    for(i=0; i<10; i++)
        servo_base->decreasePWM();
    for(i=0; i<10; i++)
        servo_base->increasePWM();
    for(i=0; i<10; i++)
        servo_panel->decreasePWM();
    for(i=0; i<10; i++)
        servo_panel->increasePWM();
}