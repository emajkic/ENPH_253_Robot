#include <Arduino.h>

#include "ServoContinuous.h"
#include "Constants.h"
#include "PinSetup.h"

ServoContinuous::ServoContinuous(int servoPin)
{
    this->servoPin = servoPin;
    this->attached = false;
}

/*
 * Sets servo speed and direction. If valid direction is not provided, will set the speed to 0.
 *
 * @param speed         int in [0,65]
 * @param direction     CW or CCW; dir in which the motor should spin
 */
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
 * Attach servo object to a PWM channel
 *
 * @return true if successfully attached, false otherwise
 */
boolean ServoContinuous::attach()
{

    ledcSetup(pwmChannelContServo, SERVO_CONT_FREQ, SERVO_CONT_RESOLUTION); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
    ledcAttachPin(servoPin, pwmChannelContServo);
    this->pwmChannel = pwmChannelContServo;

    this->attached = true;
    return true;
}

/*
 * Detach servo object to a PWM channel
 *
 * @return true if successfully detached, false otherwise
 */
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
 * Sets speed to 0
 */
void ServoContinuous::stop()
{
    setSpeed(0, ThetaDirection::CW);
}