#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"
#include <cmath>

#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"
#include "Utils.h"

PID::PID(Motor &leftMotor, Motor &rightMotor) : leftMotor(leftMotor), rightMotor(rightMotor) { //Should we rename these to pinCCW and pinCW s.t. know which is which
    this->KP = KP_LINE_FOLLOWER;
    this->KI = KI_LINE_FOLLOWER;
    this->KD = KD_LINE_FOLLOWER;

    this->error = 0;
    this->lastError = 0;

    this->lastTime = 0;
}

/*
* Use PID control loop
*/
void PID::usePID(int baseSpeed) {
    doPIDLine(baseSpeed);
}

/*
* Set PID error to 0
*/
void PID::resetPID() {
    this->error = 0.0;
    this->lastError = 0.0;
}

//DEBUG
int count1 = 0;

void PID::doPIDLine(int baseSpeed) {
    error = getErrorLine();

    unsigned long currentTime = micros();
    double dt = static_cast<double>(currentTime - lastTime) ; // AA: using micro seconds --> see by testing if this is closer to characteristic time
    if (dt <= 1) dt = 1; // changed these from 0.000001 s (converted back to micros)

    double derivativeError = (error - lastError) / dt;

    lastError = error;
    lastTime = currentTime;

    // Adjustements
    int adjustement = ((KP * error) + (KD * derivativeError));

    int newLeftSpeed = baseSpeed - adjustement;
    int newRightSpeed = baseSpeed + adjustement;

    Direction dirLeft;
    Direction dirRight;

    // Left motor adjustement
    if (newLeftSpeed < MIN_SPEED) {
        newLeftSpeed = abs(newLeftSpeed - (2 * MIN_SPEED));
        newLeftSpeed = constrain(newLeftSpeed, MIN_SPEED, MAX_SPEED);
        dirLeft = Direction::BACKWARD;
    } else if (newLeftSpeed >= MIN_SPEED) {
        newLeftSpeed = constrain(newLeftSpeed, MIN_SPEED, MAX_SPEED);     
        dirLeft = Direction::FORWARD;
    }

    // Right motor adjustement
    if (newRightSpeed < MIN_SPEED) {
        newRightSpeed = abs(newRightSpeed - (2 * MIN_SPEED));
        newRightSpeed = constrain(newRightSpeed, MIN_SPEED, MAX_SPEED);
        dirRight = Direction::BACKWARD;
    } else if (newRightSpeed >= MIN_SPEED) {
        newRightSpeed = constrain(newRightSpeed, MIN_SPEED, MAX_SPEED);     
        dirRight = Direction::FORWARD;
    }

    if (count1 >= 1000) {
        // Serial.print("KP = "); Serial.println(this->KP);
        // Serial.print("KD = "); Serial.println(this->KD);
        Serial.print("Error: "); Serial.println(error);
        Serial.print("Adjustment: "); Serial.println(adjustement);
        Serial.print(" | LeftSpeed: "); Serial.println(newLeftSpeed);
        Serial.print(" | RightSpeed: "); Serial.println(newRightSpeed);
        Serial.print(" | Right Dir: "); Serial.println(dirRight == Direction::FORWARD);
        Serial.print(" | Left Dir: "); Serial.println(dirLeft == Direction::FORWARD);
        count1=0;
    }
        
       count1++;

    leftMotor.setSpeed(newLeftSpeed, dirLeft);
    rightMotor.setSpeed(newRightSpeed, dirRight);
}   

int PID::getErrorLine() {
    int leftReading = digitalRead(QRD_PIN_LEFT);
    int rightReading = digitalRead(QRD_PIN_RIGHT);

    int err = 0;

    if (leftReading == LINE_BLACK && rightReading == LINE_BLACK) { //Threshold set by hardware (comparator)
        err = 0;
    } else if (leftReading == LINE_BLACK && rightReading == LINE_WHITE) {
        err = 1;
    } else if (leftReading == LINE_WHITE && rightReading == LINE_BLACK) {
        err = -1;
    } else if (leftReading == LINE_WHITE && rightReading == LINE_WHITE) {
        if (lastError > 0) {
            err = 2;
        } else if (lastError <= 0) { //TODO: CHECK THIS -> WHAT IF LASTERR = 0
            err = -2;
        } 
    }

    // Low pass filter
    if(abs(lastError - err) >= 2){
        err = lastError;
    }

    return err;
}
