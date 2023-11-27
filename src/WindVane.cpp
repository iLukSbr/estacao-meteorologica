#include "pch.h"
#include "WindVane.h"

WindVane::WindVane():
    magnetometer(new GY511()),
    heading(0)
{
    info[3] = '\0';
    start();
}

WindVane::~WindVane()
{
    delete magnetometer;
}

const char* WindVane::getDirection() const{
    return info;
}

void WindVane::makeJson(JsonDocument& doc){
    doc[F(WINDVANE_KEY)] = getDirection();
}

void WindVane::print() const{
    Serial.println(F("Reed switches wind vane:"));
    Serial.print(F("magnetometer direction = "));
    Serial.println(magnetometer->getDirection());
    Serial.print(F("wind direction = "));
    Serial.println(getDirection());
}

void WindVane::read(){
    Serial.println(F("Reading reed switches wind vane..."));
    heading = fixed_heading;
    if(digitalRead(RS_PIN1)){
        Serial.println(F("Reed switch 1 activated!"));
        heading += 0;
    }
    else if(digitalRead(RS_PIN2)){
        Serial.println(F("Reed switch 2 activated!"));
        heading += 22.5;
    }
    else if(digitalRead(RS_PIN3)){
        Serial.println(F("Reed switch 3 activated!"));
        heading += 45;
    }
    else if(digitalRead(RS_PIN4)){
        Serial.println(F("Reed switch 4 activated!"));
        heading += 67.5;
    }
    else if(digitalRead(RS_PIN5)){
        Serial.println(F("Reed switch 5 activated!"));
        heading += 90;
    }
    else if(digitalRead(RS_PIN6)){
        Serial.println(F("Reed switch 6 activated!"));
        heading += 112.5;
    }
    else if(digitalRead(RS_PIN7)){
        Serial.println(F("Reed switch 7 activated!"));
        heading += 135;
    }
    else if(digitalRead(RS_PIN8)){
        Serial.println(F("Reed switch 8 activated!"));
        heading += 157.5;
    }
    else if(digitalRead(RS_PIN9)){
        Serial.println(F("Reed switch 9 activated!"));
        heading += 180;
    }
    else if(digitalRead(RS_PIN10)){
        Serial.println(F("Reed switch 10 activated!"));
        heading += 202.5;
    }
    else if(digitalRead(RS_PIN11)){
        Serial.println(F("Reed switch 11 activated!"));
        heading += 225;
    }
    else if(digitalRead(RS_PIN12)){
        Serial.println(F("Reed switch 12 activated!"));
        heading += 247.5;
    }
    else if(digitalRead(RS_PIN13)){
        Serial.println(F("Reed switch 13 activated!"));
        heading += 270;
    }
    else if(digitalRead(RS_PIN14)){
        Serial.println(F("Reed switch 14 activated!"));
        heading += 292.5;
    }
    else if(digitalRead(RS_PIN15)){
        Serial.println(F("Reed switch 15 activated!"));
        heading += 315;
    }
    else if(digitalRead(RS_PIN16)){
        Serial.println(F("Reed switch 16 activated!"));
        heading += 337.5;
    }
    else
        heading += 0;
    if(heading >= 360.f)
        heading -= 360.f;
    unsigned long a = (heading>-0.5 ? heading/22.5 : (heading+360)/22.5);
	unsigned long r = a - (int)a;
	byte part = (r>=.5 ? ceil(a) : floor(a));
	info[0] = directions[part][0];
	info[1] = directions[part][1];
	info[2] = directions[part][2];
}

void WindVane::start(){
    Serial.println(F("Starting reed switches wind vane..."));
    pinMode(RS_PIN1, INPUT);
    pinMode(RS_PIN2, INPUT);
    pinMode(RS_PIN3, INPUT);
    pinMode(RS_PIN4, INPUT);
    pinMode(RS_PIN5, INPUT);
    pinMode(RS_PIN6, INPUT);
    pinMode(RS_PIN7, INPUT);
    pinMode(RS_PIN8, INPUT);
    pinMode(RS_PIN9, INPUT);
    pinMode(RS_PIN10, INPUT);
    pinMode(RS_PIN11, INPUT);
    pinMode(RS_PIN12, INPUT);
    pinMode(RS_PIN13, INPUT);
    pinMode(RS_PIN14, INPUT);
    pinMode(RS_PIN15, INPUT);
    pinMode(RS_PIN16, INPUT);
    magnetometer->read();
    delay(100);
    magnetometer->print();
    fixed_heading = magnetometer->getHeading();
    started = true;
    Serial.println(F("Reed switches wind vane OK!"));
}