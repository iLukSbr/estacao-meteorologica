/* Solar Tracker */
/* P.S. This start() has do...while and read() has !gyro->isMoving() blocking */

#include "pch.h"
#include "SolarTracker.h"

SolarTracker::SolarTracker():
    light_change_detected(false)
{
    measure_delay = 100;
    start();
}

SolarTracker::~SolarTracker(){
    delete gyro;
    delete ldr1;
    delete ldr2;
    delete ldr3;
    delete ldr4;
    delete servo_base;
    delete servo_panel;
}

void SolarTracker::checkLightChange(){
    bool move_allowed;
    float mean1_2 = (ldr1->getIlluminance() + ldr2->getIlluminance())/2.f;
    float mean3_4 = (ldr3->getIlluminance() + ldr4->getIlluminance())/2.f;
    float mean1_4 = (ldr1->getIlluminance() + ldr4->getIlluminance())/2.f;
    float mean2_3 = (ldr2->getIlluminance() + ldr3->getIlluminance())/2.f;
    float dif_x = mean1_4 - mean2_3;
    float dif_y = mean1_2 - mean3_4;
    light_change_detected = false;
    if(-TOLERANCE > dif_x || dif_x > TOLERANCE){
        lightChangeDetected();
        if(servo_panel->getServoAngle() > 90){
            if(mean1_4 > mean2_3){
                move_allowed = servo_base->increaseAngle();
                Serial.println(F("Turning right"));
                if(!move_allowed)
                    flip();
            }
            else if(mean2_3 > mean1_4){
                move_allowed = servo_base->decreaseAngle();
                Serial.println(F("Turning left"));
                if(!move_allowed)
                    flip();
            }
        }
        else{
            if(mean1_4 > mean2_3){
                move_allowed = servo_base->decreaseAngle();
                Serial.println(F("Turning left"));
                if(!move_allowed)
                    flip();
            }
            else if(mean2_3 > mean1_4){
                move_allowed = servo_base->increaseAngle();
                Serial.println(F("Turning right"));
                if(!move_allowed)
                    flip();
            }
        }            
    }
    if(-TOLERANCE > dif_y || dif_y > TOLERANCE){
        if(mean1_2 < mean3_4 && servo_panel->getServoAngle() > SERVO_PANEL_MIN){
            lightChangeDetected();
            Serial.println(F("Turning backward"));
            servo_panel->decreaseAngle();
        }
        else if(mean1_2 > mean3_4 && servo_panel->getServoAngle() < SERVO_PANEL_MAX){
            lightChangeDetected();
            Serial.println(F("Turning forward"));
            servo_panel->increaseAngle();
        }
    }
}

void SolarTracker::checkServosMovement(){
    gyro->read();
    if(!gyro->isMoving()){
        Serial.println(F("A servo motor is blocked!"));
        servo_panel->unblock();
        servo_base->unblock();
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
    // gyro->read();
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
    // gyro->print();
}

void SolarTracker::read(){
    // gyro->read();
    ldr1->read();
    ldr2->read();
    ldr3->read();
    ldr4->read();
    checkLightChange();
    // if(light_change_detected)
    //     checkServosMovement();
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
    // do{
    //     gyro = new ITGMPU6050();
    //     delay(10);
    // }while(!gyro->isStarted());
    started = true;
}


void SolarTracker::makeJson(JsonDocument& doc){// Create JSON entries
    doc[F("direcaoPlacaSolar")] = getDirection();
}