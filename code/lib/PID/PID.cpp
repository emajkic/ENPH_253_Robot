#include <Arduino.h>
#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"

PID::PID(PIDType pidType, Motor &leftMotor, Motor &rightMotor) : leftMotor(leftMotor), rightMotor(rightMotor) { //Should we rename these to pinCCW and pinCW s.t. know which is which
    switch (pidType)
    {
    case PIDType::LineFollower:
        this->KP = KP_LINE_FOLLOWER;
        this->KI = KI_LINE_FOLLOWER;
        this->KD = KD_LINE_FOLLOWER;
        break;
    case PIDType::CompassFollower:
        this->KP = KP_COMPASS_FOLLOWER;
        this->KI = KI_COMPASS_FOLLOWER;
        this->KD = KD_COMPASS_FOLLOWER;        
        break;
    default:
        break;
    } 

    this->error = 0;
    this->lastError = 0;
    this->lastDifferentError = 0;

    this->pidType = pidType;

    this->lastTime = 0;
    this->timeOfLastChange = 0;

    pinMode(LEFT_QRD_PIN, INPUT);
    pinMode(RIGHT_QRD_PIN, INPUT);
}

/*
* Use PID control loop
*/
void PID::usePID() {
    // Only implement PD control for now (assume KP will = 0)
    switch (pidType)
    {
    case PIDType::LineFollower:
        doPIDLine();
        break;
    case PIDType::CompassFollower:
        doPIDCompass();
        break;
    default:
        break;
    } 
}

void PID::doPIDLine() {
    this->error = getErrorLine();

    int prevLeftSpeed = leftMotor.getSpeed();
    int prevRightSpeed = rightMotor.getSpeed();

    //implement I control if needed

    double derivativeError;

    if (lastError != error) {
        unsigned long deltaTime = micros() - lastTime;
        if (deltaTime == 0) deltaTime = 1;
        derivativeError = (error - lastError) / static_cast<double>(deltaTime);

        lastDifferentError = error;
        timeOfLastChange = lastTime; 
    } else {
        derivativeError = (error - lastError) / (micros() - timeOfLastChange);
    }

    lastError = error;
    lastTime = micros();

    // Adjustements
    double adjustement = (this->KP * error) + (this->KD * derivativeError);
    
    int newLeftSpeed = prevLeftSpeed - adjustement;
    int newRightSpeed = prevRightSpeed + adjustement;

    newLeftSpeed = constrain(newLeftSpeed, MIN_SPEED, MAX_SPEED);
    newRightSpeed = constrain(newRightSpeed, MIN_SPEED, MAX_SPEED);

    leftMotor.setSpeed(newLeftSpeed, Direction::FORWARD);
    rightMotor.setSpeed(newRightSpeed, Direction::FORWARD);
}   

void PID::doPIDCompass() {
    // TODO: Implement3
}

int PID::getErrorLine() {
    int leftReading = digitalRead(LEFT_QRD_PIN);
    int rightReading = digitalRead(RIGHT_QRD_PIN);

    int err = 0;

    if (leftReading == BLACK && rightReading == BLACK) { //Threshold set by hardware (comparator)
        err = 0;
    } else if (leftReading == BLACK && rightReading == WHITE) {
        err = 1;
    } else if (leftReading == WHITE && rightReading == BLACK) {
        err = -1;
    } else if (leftReading == WHITE && rightReading == WHITE) {
        if (lastError > 0) {
            err = 5;
        } else if (lastError <= 0) { //TODO: CHECK THIS -> WHAT IF LASTERR = 0
            err = -5;
        } 
    }

    return err;
}

int PID::getErrorCompass () {
    // TODO: Implement
    return 0;
}