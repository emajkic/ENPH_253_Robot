#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include <cmath>

enum class Direction {
    FORWARD,
    BACKWARD
};

enum class Side {
    LEFT,
    RIGHT
};

class Motor {
    public:
       /*
       * Class constructor
       */
       Motor(int pinF, int pinB, Side side);

       /*
       * Stop motor, ie. set speed to 0
       */
       void stop();

       /*
       * Set speed of motor 
       * 
       * @param speed         speed to set the motor; int. between 0-4095
       * @param direction     direction to spin with set speed
       */
       void setSpeed(int speed, Direction direction);

       /*
       * Getters
       */
       int getSpeed();
       Direction getDirection();
       
    private:
        Direction spinDir;
        int pinF; // Forward pin
        int pinB; // Backward pin
        int speed;
        Side side;
};

#endif