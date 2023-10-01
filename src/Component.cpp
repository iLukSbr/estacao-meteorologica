/* Component */

#include "component.h"

Component::Component():
    started(false)
{

}

Component::~Component(){
    
}

bool Component::isStarted() const{
    return started;
}