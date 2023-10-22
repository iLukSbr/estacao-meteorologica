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

void SolarTracker::print() const{

}

void SolarTracker::read(){
    ldr1->read();
    ldr2->read();
    ldr3->read();
    ldr4->read();
    if(ldr1->getIlluminance() > ldr2->getIlluminance() + TOLERANCE && ldr4->getIlluminance() > ldr3->getIlluminance() + TOLERANCE){
        if(!servo_base->decreasePWM()){
            servo_base->flip();
            servo_panel->flip();
        }
        light_change_detected = true;
    }
    else if(ldr1->getIlluminance() + TOLERANCE < ldr2->getIlluminance() && ldr4->getIlluminance() + TOLERANCE < ldr3->getIlluminance()){
        if(!servo_base->increasePWM()){
            servo_base->flip();
            servo_panel->flip();
        }
        light_change_detected = true;
    }
    else
        light_change_detected = false;
    if(ldr1->getIlluminance() > ldr4->getIlluminance() + TOLERANCE && ldr2->getIlluminance() > ldr3->getIlluminance() + TOLERANCE){
        servo_panel->decreasePWM();
        light_change_detected = true;
    }
    else if(ldr1->getIlluminance() + TOLERANCE > ldr4->getIlluminance() && ldr2->getIlluminance() + TOLERANCE > ldr3->getIlluminance()){
        servo_panel->increasePWM();
        light_change_detected = true;
    }
    else
        light_change_detected = false;
    gyro->read();
    if(light_change_detected && !gyro->isMoving()){
        byte i;
        for(i=0; i<10; i++)
            servo_base->decreasePWM();
        for(i=0; i<10; i++)
            servo_base->increasePWM();
        for(i=0; i<10; i++)
            servo_panel->decreasePWM();
        for(i=0; i<10; i++)
            servo_panel->increasePWM();
        this->read();
    }
}

void SolarTracker::start(){
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
    do{
        gyro = new ITGMPU6050();
        delay(10);
    }while(!gyro->isStarted());
    gyro->read();
    started = true;
}