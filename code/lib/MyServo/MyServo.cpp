#include <Arduino.h>
#include "Constants.h"
#include "MyServo.h"
#include "PinSetup.h"

const int servoFreq = 50;      // 50 Hz = 20 ms period (standard for servos)
const int servoResolution = 16; // 16-bit resolution (0–65535)

/*
* Class constructor
*
* Note: this includes PWM channel setup (different from standard servo libraries)
*/
MyServo::MyServo(int servoPin, Name name) {
    this->servoPin = servoPin; 
    this->name = name;

    switch (name)
    {
    case Name::CLAW1:
        ledcSetup(pwmChannelC1, servoFreq, servoResolution); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
        ledcAttachPin(servoPin, pwmChannelC1); 
        this->pwmChannel = pwmChannelC1;  // assign pwm channel 
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
}

/*
* Move servo to specified angle
* 
* @param angle      angle to set the motor; int. between 0-180
*/
void MyServo::moveServo(int angle) {
   // Convert angle (0–180) to pulse width (1000–2000 µs)
  int pulseWidth_us = 1000 + (angle * 1000) / 180;

  // Convert pulse width to duty cycle (out of 65535)
  uint32_t duty = (uint32_t)((pulseWidth_us / 20000.0) * 65535);

  ledcWrite(pwmChannel, duty);

  this->angle = angle; 

}

/*
* Getters
*/
int MyServo::getAngle() {
    return this->angle; 
}
       