#include <Arduino.h>

#include "ServoESP.h"
#include "Constants.h"
#include "PinSetup.h"

ServoESP::ServoESP(int servoPin, Name name, int chassisZero)
{
    this->servoPin = servoPin;
    this->name = name;
    this->chassisZero = chassisZero; 

    this->attached = false;
    this->absoluteAngle = 0; 
    this->relativeAngle = -chassisZero; // talk abt 
}

/*
 * Initialise --> connect the servo to a pwm channel
 *
 * @return false if failed to connect
 */
boolean ServoESP::attach()
{
    switch (name)
    {
    case Name::CLAW1:
        ledcSetup(pwmChannelC1, servoFreq, servoResolution); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
        ledcAttachPin(servoPin, pwmChannelC1);
        this->pwmChannel = pwmChannelC1;
        break;
    case Name::CLAW2:
        ledcSetup(pwmChannelC2, servoFreq, servoResolution);
        ledcAttachPin(servoPin, pwmChannelC2);
        this->pwmChannel = pwmChannelC2;
        break;
    case Name::LIDAR_LEFT:
        ledcSetup(pwmChannelLL, servoFreq, servoResolution);
        ledcAttachPin(servoPin, pwmChannelLL);
        this->pwmChannel = pwmChannelLL;
        break;
    case Name::LIDAR_RIGHT:
        ledcSetup(pwmChannelLR, servoFreq, servoResolution);
        ledcAttachPin(servoPin, pwmChannelLR);
        this->pwmChannel = pwmChannelLR;
        break;
    default:
        break;
    }

    this->attached = true;
    return true; 
}

/*
 * disconnect the servo from the pwm channel
 *
 * return: false if failed to disconnect (because the servo wasn't connected previously)
 */
boolean ServoESP::detach()
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
 * Move servo to specified angle 
 * @param angle    angle to set the motor; int. between 0-180
 */
void ServoESP::moveServo(int angle)
{
    // 1. Calculate duty based on 500us to 2500us 
    int pulseMin = 500; // in microseconds
    int pulseMax = 2500;
    angle = constrain(angle, 0, 180);
    int pulseWidth_us = map(angle, 0, 180, pulseMin, pulseMax);

    // 2. Convert to duty cycle
    uint32_t maxDuty = (1 << servoResolution) - 1;
    uint32_t duty = ((uint32_t)pulseWidth_us * servoFreq * maxDuty) / 1000000;

    ledcWrite(this->pwmChannel, duty);

    this->absoluteAngle = angle;
    this->relativeAngle = angle - chassisZero; 
}

/*
 * Move servo to specified angle relative to the chassis 0 (the angle parallel to the axis, pointing to the front of the robot)
 *
 * @param angle    angle to set the motor; int. between 0 -> (180 - chassisZero)
 */
void ServoESP::moveServoChassis(int angle)
{
    int actualAngle = angle + chassisZero; 
    moveServo(actualAngle); 
}

/*
 * Getters
 */
int ServoESP::getAbsoluteAngle()
{
    return this->absoluteAngle;
}

int ServoESP::getRelativeAngle()
{
    return this->relativeAngle;
}