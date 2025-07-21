#include <Arduino.h>
#include <map> // Required header for std::map

#include "Constants.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "Motor.h"
#include "Claw.h"

const int clampTime = 500;

Claw::Claw(ServoESP &servo1, ServoESP &servo2, Motor clampMotor) : servo1(servo1), servo2(servo2), clampMotor(clampMotor)
{

    //  Claw //
    // const int CLAW_SERVO_1_PIN = 12;
    // const int CLAW_SERVO_2_PIN = 13;
    // const int ROTARY_IN_CLK_PIN = 36;
    // const int ROTARY_IN_DT_PIN = 39;
    // const int CLAW_HOME_SWITCH_PIN = 15;
    // const int CLAMP_MOTOR_PIN = 4;
    // const int ROTARY_MOTOR_PIN = 2;

    // const int HALL_OUTPUT_PIN = 0;
}

/*
 * Locates home position -> will spin DC motor until limit switch activated, and use that position to orient itself in the theta dir
 */
void Claw::home()
{
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
void Claw::moveClaw(int x, int y, int theta)
{

    std::map<std::string, int> angles = getAngles(x, y);
    servo1.moveServo(angles.at("alpha"));
    servo2.moveServo(angles.at("beta"));

    moveTheta(theta);
}

/*
 * Moves claw to basket (this will be the home position)
 */
void Claw::basket()
{
    std::map<std::string, int> angles = getAngles(xbasket, ybasket);
    servo1.moveServo(angles.at("alpha"));
    servo2.moveServo(angles.at("beta"));

    moveTheta(thetaBasket);
}

/*
 * Clamp the pet once hall signal detected
 */
void Claw::clamp()
{
    int startTime = millis();

    clampMotor.setSpeed(400, Direction::FORWARD);

    while (millis() - startTime < clampTime)
    {
        // just wait here
    }

    clampMotor.stop();

    // make more sophisticated once Yuri implements the mechanism --> calculate the acc time period req'd
}

/*
 * Unclamp the pet once the claw has reached the basket
 */
void Claw::unclamp()
{
    int startTime = millis();

    clampMotor.setSpeed(400, Direction::BACKWARD);

    while (millis() - startTime < clampTime)
    {
        // just wait here
    }

    clampMotor.stop();

    // make more sophisticated once Yuri implements the mechanism --> calculate the acc time period req'd
    // write this low -> do we need limit switches on the edges of the linear thingy
}

/*
 * returns map with alpha and beta to move the servos to in degrees; alpha and beta are both between 0 and 90 degrees
 */
std::map<std::string, double> getAngles(int x, int y)
{
    std::map<std::string, double> angles;

    double m = static_cast<double>(x);
    double n = static_cast<double>(y);
    double l = sqrt(m * m + n * n);

    double alpha_rad = -(atan2(n, m) + acos((l2 * l2 - l1 * l1 - l * l) / (-2.0 * l1 * l))) + alphaO;
    double beta_rad = acos((l * l - l2 * l2 - l1 * l1) / (-2.0 * l2 * l1)) - betaO;

    angles["alpha"] = alpha_rad * 180.0 / PI;
    angles["beta"] = beta_rad * 180.0 / PI;

    return angles;
}

void moveTheta()
{

    // add theta code here --> currently not set up bc rotary enc not set up
}