#ifndef CLAW_H
#define CLAW_H

#include <Arduino.h>
#include <ServoESP.h>
#include <map> // Required header for std::map

class Claw
{
public:
    Claw(ServoESP &servo1, ServoESP &servo2, Motor clampMotor);

    /*
     * Locates home position -> will spin DC motor until limit switch activated, and use that position to orient itself in the theta dir
     */
    void home();

    /*
     * Moves claw to position specified by x, y, and theta
     *
     *
     * @param x     position in axis perpendicular to chassis sides (will come from lidar)
     * @param y     position in the cartesian z axis
     * @param theta    angle of lazy susan/bottom dc motor (will also come from lidar, and aside from the window will always be 0, 90, 180, or 270)
     */
    void moveClaw(int x, int y, int theta);

    /*
     * Moves claw to basket (this will be the home position)
     */
    void basket();

    /*
     * Clamp the pet once hall signal detected --> HOW DO I DO THIS? DO WE HAVE AN INTERRUPT THE HALL'S INPUT PIN AND HAVE THE ISR CHANGE A BOOLEAN THAT ONCE ACTIVATED, CAUSES CLAMPING?
                                                    --> OR DO WE WANT TO JUST CALL THIS FUNCTION
     */
    void clamp();

    /*
     * Unclamp the pet once the claw has reached the basket
     */
    void unclamp();

private:
    ServoESP &servo1;
    ServoESP &servo2;
    Motor &clampMotor; 
    
    // AM I MAKING DC MOTOR CLASS/OBJS TO ASSOCIATE WITH THIS OR NO
   
    /*
     * returns map with alpha and beta to move the servos to in degrees; alpha and beta are both between 0 and 90 degrees
     */
    std::map<std::string, int> getAngles(int x, int y);

    void moveTheta(int theta); 
};

#endif