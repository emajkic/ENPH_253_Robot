#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>
#include <ServoESP.h>

class Claw
{
public:
    Claw(ServoESP& servo1, ServoESP& servo2, int thetaPin, int clampPin);

    /*
     * Moves claw to position specified by angle1, angle2, and angle3
     *
     *
     * @param angle1    angle of lazy susan/bottom dc motor --> only 0, 90, 180, or 270
     * @param angle2    angle of servo1
     * @param angle3    angle of servo2
     */
    bool moveClaw(int angle1, int angle2, int angle3);

    /*
     * Clamp the pet once hall signal detected --> HOW DO I DO THIS? DO WE HAVE AN INTERRUPT 
                                                   THE HALL'S INPUT PIN AND HAVE THE ISR CHANGE A BOOLEAN THAT ONCE ACTIVATED, 
                                                   CAUSES CLAMPING?
     */
    void clamp();

    

    /*
    * 
    */
    bool initialiseLidar();

private:
    ServoESP &servo1;
    ServoESP &servo2;
    int sclPin;
    int sdaPin; // these are i2c enabled pins for communicating with the LiDAR

    uint16_t singleMeasurement(); 
};

#endif