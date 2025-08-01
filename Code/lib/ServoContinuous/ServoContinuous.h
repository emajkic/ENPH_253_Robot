// rotary servo will be on channel 12
// this class serves as a wrapper for a continuous servo and rotary encoder that is used to position our claw in the theta direction

#ifndef SERVOCONTINUOUS_h
#define SERVOCONTINUOUS_h

#include <Arduino.h>

enum class ThetaDirection { 
    CW,
    CCW
};

class ServoContinuous
{
public:
    ServoContinuous(int servoPin);

    /*
    Sets servo speed - takes in an integer between 0 and 65, and the direction (CW or CCW)
    */
    void setSpeed(int speed, ThetaDirection direction);

    /*
    Attch servo object to a PWM channel
    */
    boolean attach();

    /*
    Detach servo from it's PWMS channel
    */
    boolean detach();

    /*
    Sets speed to 0
    */
    void stop();

private:
    int servoPin; // PWM enabled pin for controlling the servo
    boolean attached;
    int pwmChannel;
};

#endif