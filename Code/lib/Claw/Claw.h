#ifndef Claw_h
#define Claw_h

#include <Arduino.h>
#include <map> // Required header for std::map

#include "Constants.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "ServoContinuous.h"

extern portMUX_TYPE mux;

extern volatile int encoderPos; // will be limited between 0 - 95 (one full rotation)
extern volatile bool clkFlag;
extern volatile bool dtFlag;
extern volatile uint8_t reading;
extern volatile bool homed; // Flag to check if the servo is homed
extern int oldEncPos;

// ISRS //
void IRAM_ATTR handleCLK();
void IRAM_ATTR handleDT();
void IRAM_ATTR handleLimitSwitch(); 

// NOTE: need to do attachInterrupt along with pinMode in setup //

class Claw {
public:
    Claw(ServoESP &servo1, ServoESP &servo2, ServoESP &clampMotor, ServoContinuous &thetaMotor);

    /*
     * Locates home position -> will spin DC motor until limit switch activated, and use that position to orient itself in the theta dir
     */
    void homeTheta();

    /*
     * moves claw to 0 in x and y
     */
    void homeXY();

    /*
     * Moves claw to position specified by x, y, and theta
     *
     *
     * @param x     position in axis perpendicular to chassis sides (will come from lidar)
     * @param y     position in the cartesian z axis
     * @param theta    ticks of lazy susan/bottom dc motor - must be a value form (0-95) --> if you give it a disallowed value, the claw will not move
     * 
     * NOTE: multiples of 24 are cardinal directions
     */
    void moveClaw(int x, int y, int theta);

    /*
     * Moves claw to basket (this will be the artificial home position -> ie it's default even though the x,y,theta values may not all be 0)
     */
    void basket();

    /*
     * Moves claw to it's archway position
     */
    void archwayPosition();

    /*
     * Moves claw to it's window position
     */
    void windowPosition();

    /*
     * Moves claw to its ramp drop-off position
     */
    void rampPosition();

    /*
    * Moves claw to its most stable drive position
    */
    void drivePosition();

    /*
     * Clamp the pet once hall signal detected
     */
    void clamp();

    /*
     * Unclamp the pet once the claw has reached the basket
     */
    void unclamp();

    /*
     * Reads associated hall sensor
     */
    bool readHall();

    /*
     * Sweeps the head of the claw to search for signal from hall effect signal/pet
     *
     * The function will sweep the head of the claw from currrentPos-HALL_SWEEP_LENGTH/2 to currentPos+HALL_SWEEP_LENGTH/2
     */
    bool sweepForHall();

    // encoder:
    void moveTheta(int theta, int speed); // MAKE THIS PRIVATE AGAIN POST TESTING

private:
    ServoESP &servo1;
    ServoESP &servo2;
    ServoESP &clampMotor;
    ServoContinuous &thetaMotor;

    ThetaDirection lastDir; 

    /*
     * returns map with alpha and beta to move the servos to in degrees; alpha and beta are both between 0 and 90 degrees
     */
    std::map<std::string, double> getAngles(int x, int y);

    

    void stopTheta();
};

#endif