#include <Arduino.h>
#include "driver/ledc.h"

#include "Constants.h"
#include "Motor.h"
#include "PinSetup.h"

/*
* Class constructor
*/
Motor::Motor(int pinF, int pinB, Side side) { //Should we rename these to pinCCW and pinCW s.t. know which is which
    this->pinF = pinF; 
    this->pinB = pinB;
    this->side = side;

    switch (side)
    {
    case Side::LEFT:
        ledcSetup(pwmChannelFL, 50, 12); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
        ledcAttachPin(pinF, pwmChannelFL);

        ledcSetup(pwmChannelBL, 50, 12);
        ledcAttachPin(pinB, pwmChannelBL);

        break;
    case Side::RIGHT:
        ledcSetup(pwmChannelFR, 50, 12); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
        ledcAttachPin(pinF, pwmChannelFR);

        ledcSetup(pwmChannelBR, 50, 12);
        ledcAttachPin(pinB, pwmChannelBR);
        break;
    default:
        break;
    }
}

/*
* Stop motor, ie. set speed to 0
*/
void Motor::stop() {
    switch (this->side)
    {
    case Side::LEFT:
        ledcWrite(pwmChannelFL, 0); 
        ledcWrite(pwmChannelBL, 0); 
        break;
    case Side::RIGHT:
        ledcWrite(pwmChannelFR, 0); 
        ledcWrite(pwmChannelBR, 0); 
        break;
    default:
        break;
    }
}

/*
* Set speed of motor 
* 
* @param speed         speed to set the motor; fraction between 0-1
* @param direction     direction to spin with set speed
*/
void Motor::setSpeed(int speed, Direction direction) {    
    switch (direction)
    {
    case Direction::FORWARD:
        switch (this->side)
        {
        case Side::LEFT:
            ledcWrite(pwmChannelFL, speed); 
            ledcWrite(pwmChannelBL, 0);
            break;
        case Side::RIGHT:
            ledcWrite(pwmChannelFR, speed); 
            ledcWrite(pwmChannelBR, 0); 
            break;  
        default:
            break;
    }
        break;
    case Direction::BACKWARD:
        switch (this->side)
        {
        case Side::LEFT:
            ledcWrite(pwmChannelFL, 0); 
            ledcWrite(pwmChannelBL, speed);
            break;
        case Side::RIGHT:
            ledcWrite(pwmChannelFR, 0); 
            ledcWrite(pwmChannelBR, speed); 
            break;   
        default:
            break;
    }
        break;
    }

    this->spinDir = direction;
    this->speed = speed;
}

/*
* Get speed of motor 
*
* @return the current speed of the motor 
*/
int Motor::getSpeed() {
    return this->speed; 
}

/*
* Get motor's direction of turning
*
* @return the current spinning direction of the motor 
*/
Direction Motor::getDirection() {
    return this->spinDir;
}