#include <Arduino.h>
#include <map> // Required header for std::map
#include "driver/adc.h"

#include "Constants.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "ServoContinuous.h"
#include "Motor.h"
#include "Claw.h"

const double X_OFFSET = 2.833;  // [cm]
const double Y_OFFSET = 5.771; // [cm]

// Interrupt Global Variables // 

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

volatile int encoderPos = 0; // will be limited between 0 - 95 (one full rotation)
volatile bool clkFlag = false;
volatile bool dtFlag = false;
volatile uint8_t reading = 0;
volatile bool homed = false; // Flag to check if the servo is homed
int oldEncPos = 0;


// ISRS //
void IRAM_ATTR handleCLK() {
    portENTER_CRITICAL_ISR(&mux);
    reading = (digitalRead(ROTARY_IN_CLK_PIN) << 1) | digitalRead(ROTARY_IN_DT_PIN);

    if (reading == 0b11 && clkFlag)
    {
        encoderPos--;

        if (encoderPos < 0)
        {
            encoderPos = 96 - abs(encoderPos % 95);
        }

        clkFlag = false;
        dtFlag = false;
    }
    else if (reading == 0b10)
    {
        dtFlag = true;
    }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR handleDT() {
    portENTER_CRITICAL_ISR(&mux);
    reading = (digitalRead(ROTARY_IN_CLK_PIN) << 1) | digitalRead(ROTARY_IN_DT_PIN);

    if (reading == 0b11 && dtFlag)
    {
        encoderPos++;

        if (encoderPos > 95)
        {
            encoderPos = encoderPos % 95 - 1;
        }

        clkFlag = false;
        dtFlag = false;
    }
    else if (reading == 0b01)
    {
        clkFlag = true;
    }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR handleLimitSwitch() {
    encoderPos = 0; // Reset encoder position when limit switch is pressed
    homed = true;   // Set the homed flag to true
}

// Class Member Functions // 

/*
 * This attaches the servo objects
 */
Claw::Claw(ServoESP &servo1, ServoESP &servo2, ServoESP &clampMotor, ServoContinuous &thetaMotor) : servo1(servo1), servo2(servo2), clampMotor(clampMotor), thetaMotor(thetaMotor) {
    servo1.attach();
    servo2.attach();
    clampMotor.attach();
    thetaMotor.attach();
}

/*
 * Locates home position -> will spin DC motor until limit switch activated, and use that position to orient itself in the theta dir
 */
void Claw::homeTheta() {
    delay(100);

    portENTER_CRITICAL(&mux);
    int currentPos = encoderPos;
    portEXIT_CRITICAL(&mux);

    if (!homed)
    {
        while (!homed)
        {
            thetaMotor.setSpeed(10, ThetaDirection::CW); // Move to home position
            currentPos = encoderPos;
            //Serial.println(currentPos);
        }
        thetaMotor.stop(); // Stop the servo after homing
    }
}

/*
 * Moves claw to 0 in x and y
 */
void Claw::homeXY() {
    unsigned long time1 = millis();
    servo1.moveServo(0);

    while (millis() - time1 < 1000)
    {
        // just wait here until first one is done moving
    }

    servo2.moveServo(0);
}

/*
 * Moves claw to position specified by x, y, and theta
 *
 *
 * @param x     position in axis perpendicular to chassis sides (will come from lidar) -- the origin is at the centre of the claw's base
 * @param y     position in the cartesian z axis
 * @param theta    angle of lazy susan/bottom dc motor (will also come from lidar, and aside from the window will always be 0, 90, 180, or 270)
 */
void Claw::moveClaw(int x, int y, int theta) {

    moveTheta(theta, 10); // speed used in dannys code

    // deal with delay
    delay(100); 

    std::map<std::string, double> angles = getAngles(x - X_OFFSET, y - Y_OFFSET);

    unsigned long time1 = millis();

    servo1.moveServo(angles.at("alpha"));

    while (millis() - time1 < 1000)
    {
        // just wait here until first one is done moving
    }

    servo2.moveServo(angles.at("beta"));

}

/*
 * Moves claw to basket (this will be the home position)
 */
void Claw::basket() {
    std::map<std::string, double> angles = getAngles(X_BASKET, Y_BASKET);
    unsigned long time1 = millis();

    servo1.moveServo(angles.at("alpha"));

    while (millis() - time1 < 1000)
    {
        // just wait here until first one is done moving
    }

    servo2.moveServo(angles.at("beta"));

    moveTheta(THETA_BASKET, 10);

    // SET THESE IN CONSTANTS.H INSTEAD OF DOING A CALCULATION EACH TIME 
}

/*
 * Moves claw to basket (this will be the home position)
 */
void Claw::archwayPosition() {
    std::map<std::string, double> angles = getAngles(X_ARCHWAY, Y_ARCHWAY);
    unsigned long time1 = millis();

    servo1.moveServo(angles.at("alpha"));

    while (millis() - time1 < 1000)
    {
        // just wait here until first one is done moving
    }

    servo2.moveServo(angles.at("beta"));

    moveTheta(THETA_ARCHWAY, 10);

    // SET THESE IN CONSTANTS.H
}



/*
 * Clamp the pet once hall signal detected
 */
void Claw::clamp() {
    clampMotor.moveServo(10);
}

/*
 * Unclamp the pet once the claw has reached the basket
 */
void Claw::unclamp() {
    clampMotor.moveServo(90);
}

bool Claw::readHall() {
    int hallReading = adc1_get_raw(ADC1_CHANNEL_0); // reads the analog value of ADC1_CHANNEL_0 (pin 36)

    if (abs(hallReading - HALL_MIDPOINT) > HALL_THRESHOLD)
    {
        return true;
    }

    return false;
}

/*
 * returns map with alpha and beta to move the servos to in degrees; alpha and beta are both already adjusted for the gearing of the claw
 */
std::map<std::string, double> Claw::getAngles(int x, int y) {
    std::map<std::string, double> angles;

    double m = static_cast<double>(x);
    double n = static_cast<double>(y);
    double l = sqrt(m * m + n * n);

    double alpha_rad = -(atan2(n, m) + acos((L2 * L2 - L1 * L1 - l * l) / (-2.0 * L1 * l))) + ALPHA_0;
    double beta_rad = acos((l * l - L2 * L2 - L1 * L1) / (-2.0 * L2 * L1)) - BETA_0;

    angles["alpha"] = GEAR_RATIO * alpha_rad * 180.0 / PI; // multiplying by 2 for gear ratio
    angles["beta"] = GEAR_RATIO * beta_rad * 180.0 / PI;

    return angles;
}

void Claw::moveTheta(int theta, int speed) {

    portENTER_CRITICAL(&mux); // critical section in case interrupt is triggered inside this assignment 
    int currentPos = encoderPos;
    portEXIT_CRITICAL(&mux);

    if (theta < 0 || theta > 95 || theta == currentPos)
    {
        return;
    }

    ThetaDirection direction = ThetaDirection::CCW;

    if ((theta - currentPos + 96) % 96 <= (currentPos - theta + 96) % 96) 
    {
        direction = ThetaDirection::CCW;
    }
    else
    {
        direction = ThetaDirection::CW;
    }

    while (currentPos != theta)
    {
        if (abs(currentPos - theta) < 2 && speed > 0)
        {
            speed = 2; // Slow down when close to target
        }
        // otherwise the speed is maintained

        if (direction == ThetaDirection::CW)
        {
            thetaMotor.setSpeed(speed, ThetaDirection::CW);
            currentPos = encoderPos;
        //    Serial.println(currentPos);
        }
        else
        {
            thetaMotor.setSpeed(speed, ThetaDirection::CCW);
            currentPos = encoderPos;
        //    Serial.println(currentPos);
        }

        delay(100); // Adjust delay as needed for smoother movement
    }

    thetaMotor.stop(); // Stop the servo
}
