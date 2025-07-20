#ifndef ServoESP_h
#define ServoESP_h

#include <Arduino.h>

enum class Name { // do something here for the PWM channel? 
    CLAW1,
    CLAW2, 
    LIDAR_LEFT, 
    LIDAR_RIGHT
};

class ServoESP {
    public:
       ServoESP(int servoPin, Name name);

       /*
       * Move servo to specified angle
       * 
       * @param angle         angle to set the motor; int. between 0-180
       */
       void moveServo(int angle);

       /*
       * Attch servo object to a PWM channel
       */
       boolean attach();

       /*
       * Detach servo from it's PWMS channel
       */
       boolean detach();

       int getAngle();
       
    private:
        int servoPin; //PWM enabled pin for controlling the servo 
        int angle;
        Name name;
        boolean attached; 
        int pwmChannel;
};

#endif