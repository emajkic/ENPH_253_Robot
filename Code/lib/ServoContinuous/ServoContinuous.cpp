#include <Arduino.h>

#include "ServoContinuous.h"
// #include "Constants.h"
// #include "PinSetup.h"

const int pwmChannelContSer = 0;
const int servoContFreq = 250;
const int servoContResolution = 8;

ServoContinuous::ServoContinuous(int servoPin)
{
    this->servoPin = servoPin;
    this->attached = false;
}

/*

Sets servo speed and direction.
If valid direction is not provided, will set the speed to 0.*
@param speed         int in [0,65]
@param direction     CW or CCW; dir in which the motor should spin*/
void ServoContinuous::setSpeed(int speed, ThetaDirection direction)
{
    uint32_t duty = 0;
    switch (direction)
    {
    case ThetaDirection::CW:
        duty = (92 - speed);
        break;
    case ThetaDirection::CCW:
        duty = (98 + speed);
        break;
    default:
        duty = 95; // Set to neutral position
        break;
    }

    if (speed <= 0 || speed > 65)
    {
        duty = 95; // Set to neutral position
    }
    ledcWrite(this->pwmChannel, duty);
}

/*

Initialise --> connect the servo to a pwm channel*
@return false if failed to connect*/
boolean ServoContinuous::attach()
{

    ledcSetup(pwmChannelContSer, servoContFreq, servoContResolution); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
    ledcAttachPin(servoPin, pwmChannelContSer);
    this->pwmChannel = pwmChannelContSer;

    this->attached = true;
    return true;
}

/*

disconnect the servo from the pwm channel*
return: false if failed to disconnect (because the servo wasn't connected previously)*/
boolean ServoContinuous::detach()
{
    if (attached)
    {
        ledcDetachPin(servoPin);
        this->attached = false;
        return true;
    }
    else
    {
        return false;
    }
}

/*
    Sets speed to 0
    */
void ServoContinuous::stop(){
    setSpeed(0, ThetaDirection::CW);
}