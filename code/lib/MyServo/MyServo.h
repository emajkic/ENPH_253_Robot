#ifndef Servo_h
#define Servo_h

#include <Arduino.h>
#include <cmath>

enum class Name { // do something here for the PWM channel? 
    CLAW1,
    CLAW2, 
    LIDAR_LEFT, 
    LIDAR_RIGHT
};

class MyServo {
    public:
       /*
       * Class constructor
       *
       * Note: this includes PWM channel setup (different from standard servo libraries)
       */
       MyServo(int servoPin, Name name);

       /*
       * Move servo to specified angle
       * 
       * @param angle         angle to set the motor; int. between 0-180
       */
       void moveServo(int angle);

       /*
       * Getters
       */
       int getAngle();
       
       
    private:
        int servoPin; //PWM enabled pin for controlling the servo 
        int angle;
        Name name;
        int pwmChannel; 
};

#endif