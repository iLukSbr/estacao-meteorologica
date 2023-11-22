/* GY511 magnetometer compass and accelerometer */

#include <Wire.h>
#include <LSM303.h>

#include "GY511.h"

GY511::GY511():
    part(0),
    compass(new LSM303())
{
    start();
}

GY511::~GY511(){
    delete compass;
}

byte GY511::getDirectionPart() const{
    return part;
}

const char* GY511::getDirection() const{
    return info;
}

void GY511::print() const{
    Serial.println(F("GY-511 magnetometer:"));
    Serial.print(F("direction = "));
    Serial.println(getDirection());
}

void GY511::read(){
    Serial.println(F("Reading GY511 magnetometer..."));
    compass->read();
    float heading = compass->heading();
    unsigned long a = (heading>-0.5 ? heading/22.5 : (heading+360)/22.5);
	unsigned long r = a - (int)a;
	part = (r>=.5 ? ceil(a) : floor(a));
	info[0] = directions[part][0];
	info[1] = directions[part][1];
	info[2] = directions[part][2];
    Serial.println(F("GY511 magnetometer read!"));
}

void GY511::start(){
    Serial.println(F("Starting GY511 magnetometer..."));
    LSM303::vector<int16_t> running_min = {-257, -349, -193}, running_max = {241, 172, 257};
    compass->init();
    compass->enableDefault();
	// unsigned long startTime = millis();
    Serial.println(F("Calibrating GY511 magnetometer..."));
	// while((millis() - startTime) < GY511_CALIBRATION_DURATION){
        compass->read();
        running_min.x = min(running_min.x, compass->m.x);
        running_min.y = min(running_min.y, compass->m.y);
        running_min.z = min(running_min.z, compass->m.z);
        running_max.x = max(running_max.x, compass->m.x);
        running_max.y = max(running_max.y, compass->m.y);
        running_max.z = max(running_max.z, compass->m.z);
    // }
    compass->m_min = running_min;
    compass->m_max = running_max;
    started = true;
    Serial.println(F("GY511 magnetometer OK!"));
}
