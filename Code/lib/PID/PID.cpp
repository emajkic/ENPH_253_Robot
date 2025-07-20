#include <Arduino.h>
#include "driver/ledc.h"
#include "driver/adc.h"

#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"

PID::PID(Motor &leftMotor, Motor &rightMotor) : leftMotor(leftMotor), rightMotor(rightMotor) { //Should we rename these to pinCCW and pinCW s.t. know which is which
    this->KP = KP_LINE_FOLLOWER;
    this->KI = KI_LINE_FOLLOWER;
    this->KD = KD_LINE_FOLLOWER;

    this->error = 0;
    this->lastError = 0;
    this->lastDifferentError = 0;

    this->lastTime = 0;
    this->timeOfLastChange = 0;
    
    pinMode(LEFT_QRD_PIN, INPUT);
    pinMode(RIGHT_QRD_PIN, INPUT);
}

/*
* Use PID control loop
*/
void PID::usePID() {
    consts(); // FOR TESTING ONLY
    doPIDLine();
}

// DELETE FOR TESTING ONLY ----------------------------------------- //
void PID::consts() {
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_12); // GPIO 35
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_12); // GPIO 34
    
    this->KP = adc1_get_raw(ADC1_CHANNEL_7);
    this->KD = adc1_get_raw(ADC1_CHANNEL_6);
}

/*
* Set PID error to 0
*/
void PID::resetPID() {
    this->error = 0;
    this->lastDifferentError = 0;
    this->lastError = 0;
}

void PID::doPIDLine() {
    this->error = getErrorLine();

    // int leftPrevSpeed = this->leftMotor.getSpeed();
    // int rightPrevSpeed = this->rightMotor.getSpeed();

    unsigned long currentTime = micros();
    unsigned long deltaTime;

    double derivativeError;

    if (error != lastError) {
        deltaTime = currentTime - lastTime;
        if (deltaTime == 0) deltaTime = 1;

        derivativeError = static_cast<double>(error - lastError) / static_cast<double>(deltaTime);

        lastDifferentError = error;
        timeOfLastChange = currentTime;
    } else {
        deltaTime = currentTime - timeOfLastChange;
        if (deltaTime == 0) deltaTime = 1;

        derivativeError = static_cast<double>(error - lastError) / static_cast<double>(deltaTime);
    }

    lastError = error;
    lastTime = currentTime;

    // Adjustements
    double adjustement = ((this->KP * error) + (this->KD * derivativeError));
    
    int newLeftSpeed = BASE_SPEED_L - adjustement;
    int newRightSpeed = BASE_SPEED_R + adjustement;

    int newLeftSpeedCon = constrain(newLeftSpeed, MIN_SPEED, MAX_SPEED);
    int newRightSpeedCon = constrain(newRightSpeed, MIN_SPEED, MAX_SPEED);

    leftMotor.setSpeed(newLeftSpeedCon, Direction::FORWARD);
    rightMotor.setSpeed(newRightSpeedCon, Direction::FORWARD);

    // Update object properties
    leftMotor.speed = newLeftSpeed;
    rightMotor.speed = newRightSpeed;
}   

int PID::getErrorLine() {
    int leftReading = digitalRead(LEFT_QRD_PIN);
    int rightReading = digitalRead(RIGHT_QRD_PIN);

    int err = 0;

    if (leftReading == LINE_BLACK && rightReading == LINE_BLACK) { //Threshold set by hardware (comparator)
        err = 0;
    } else if (leftReading == LINE_BLACK && rightReading == LINE_WHITE) {
        err = 1;
    } else if (leftReading == LINE_WHITE && rightReading == LINE_BLACK) {
        err = -1;
    } else if (leftReading == LINE_WHITE && rightReading == LINE_WHITE) {
        if (lastError > 0) {
            err = 5;
        } else if (lastError <= 0) { //TODO: CHECK THIS -> WHAT IF LASTERR = 0
            err = -5;
        } 
    }

    return err;
}