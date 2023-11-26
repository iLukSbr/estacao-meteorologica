/* Component */

#include "pch.h"
#include "component.h"

Component::Component():
    started(false),
    measure_delay(2000),
    stopwatch(0)
{

}

Component::~Component(){
    
}

bool Component::isStarted() const{
    return started;
}

bool Component::verifyDelay(){
    if(millis() - stopwatch >= measure_delay || !stopwatch){
        stopwatch = millis();
        return true;
    }
    else
        return false;
}

void Component::makeJson(JsonDocument& doc){
    
}