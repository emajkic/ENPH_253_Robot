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
       ServoESP(int servoPin, Name name, int chassisZero);

       /*
       * Move servo to specified angle relative to it's hardware zero
       * 
       * @param angle         angle to set the motor; int. between 0-180
       */
       void moveServo(int angle);

       /*
       * Move servo to specified angle relative to the chassis zero 
       * 
       * @param angle         angle to set the motor; int. between 0 -> (180-chassis zero)
       */
       void moveServoChassis(int angle);

       /*
       * Attch servo object to a PWM channel
       */
       boolean attach();

       /*
       * Detach servo from it's PWMS channel
       */
       boolean detach();

       int getAbsoluteAngle();

       int getRelativeAngle();
       
    private:
        int servoPin; //PWM enabled pin for controlling the servo 
        int absoluteAngle; // angle of servo relative to hardware zero 
        int relativeAngle; // angle of servo relative to chassisZero
        int chassisZero; 
        Name name;
        boolean attached; 
        int pwmChannel;
};

#endif