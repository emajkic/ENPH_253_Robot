// rotary servo will be on channel 12
// this class serves as a wrapper for a continuous servo and rotary encoder that is used to position our claw in the theta direction

#ifndef SERVOCONTINUOUS_h
#define SERVOCONTINUOUS_h

#include <Arduino.h>

enum class ThetaDirection
{
    CW,
    CCW
};

class ServoContinuous
{
public:
    ServoContinuous(int servoPin);

    /*
     * Sets servo speed and direction. If valid direction is not provided, will set the speed to 0.
     *
     * @param speed         int in [0,65]
     * @param direction     CW or CCW; dir in which the motor should spin
     */
    void setSpeed(int speed, ThetaDirection direction);

    /*
     * Attach servo object to a PWM channel
     *
     * @return true if successfully attached, false otherwise
     */
    boolean attach();

    /*
     * Detach servo object to a PWM channel
     *
     * @return true if successfully detached, false otherwise
     */
    boolean detach();

    /*
     * Sets speed to 0
     */
    void stop();

private:
    int servoPin; // PWM enabled pin for controlling the servo
    boolean attached;
    int pwmChannel;
};

#endif