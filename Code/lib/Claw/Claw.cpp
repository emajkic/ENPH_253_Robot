#include <Arduino.h>
#include <map> // Required header for std::map

#include "Constants.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "Claw.h"

const int xbasket = 10; 
const int ybasket = 10; // both in cm, measure tomorrow 

Claw::Claw(ServoESP &servo1, ServoESP &servo2, int thetaPin, int clampPin, int homeSwitch, int alphaO, int betaO, int l1, int l2) : servo1(servo1), servo2(servo2), thetaPin(thetaPin), clampPin(clampPin), alphaO(alphaO), betaO(betaO), l1(l1), l2(l2)
{
        // LATER, WE WILL HAVE ROTARY ENCODER OBJ AS WELL
}

/*
 * Locates home position -> will spin DC motor until limit switch activated, and use that position to orient itself in the theta dir
 */
void Claw::home(){
/*
 for this function, wait until danny integrates. Algo is as follows: 

 1. write the motor HI 
 2. (there is an interrupt attached to the homeSwitch pin) when homeSwitch is HI, cut the motor
 3. save that as zero position of rotary enc. (the one it was at when the enc. interrupt was triggered)
 4. move claw to that position if it overshoots

*/

}

/*
 * Moves claw to position specified by x, y, and theta
 *
 *
 * @param x     position in axis perpendicular to chassis sides (will come from lidar)
 * @param y     position in the cartesian z axis
 * @param theta    angle of lazy susan/bottom dc motor (will also come from lidar, and aside from the window will always be 0, 90, 180, or 270)
 */
void Claw::moveClaw(int x, int y, int theta){

    std::map<std::string, int> angles = getAngles(x,y); 
    servo1.moveServo(angles.at("alpha")); 
    servo2.moveServo(angles.at("beta")); 

    moveTheta(theta); 
}

/*
 * Moves claw to basket (this will be the home position)
 */
void Claw::basket(){

    std::map<std::string, int> angles = getAngles(xbasket,ybasket); 
    servo1.moveServo(angles.at("alpha")); 
    servo2.moveServo(angles.at("beta")); 

    moveTheta(270); // will the basket be the 0 or 270
}

/*
 * Clamp the pet once hall signal detected --> HOW DO I DO THIS? DO WE HAVE AN INTERRUPT THE HALL'S INPUT PIN AND HAVE THE ISR CHANGE A BOOLEAN THAT ONCE ACTIVATED, CAUSES CLAMPING?
                                                --> OR DO WE WANT TO JUST CALL THIS FUNCTION
 */
void Claw::clamp(){

    // write this high for a set period of time? is there any other signal we need
}

/*
 * Unclamp the pet once the claw has reached the basket
 */
void Claw::unclamp(){

    // write this low -> do we need limit switches on the edges of the linear thingy

}

/*
 * returns map with alpha and beta to move the servos to in degrees; alpha and beta are both between 0 and 90 degrees
 */
std::map<std::string, int> Claw::getAngles(int x, int y){
    
    std::map<std::string, int> angles; 
    
    double l = sqrt(l1*l1+l2*l2); 

    double phi1 = atan(y/x)+acos((l2*l2-l1*l1-l*l)/(-2*l1*l)); 
    double phi2 = acos((l*l-l2*l2-l1*l1)/(-2*l2*l1)); 

    double alpha = -(phi1-alphaO); 
    double beta = phi2-betaO; 

    angles.insert({"alpha", alpha}); 
    angles.insert({"beta", beta}); 

}

void moveTheta(){

    // add theta code here --> currently not set up bc rotary enc not set up 

}