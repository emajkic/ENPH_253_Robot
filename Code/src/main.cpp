#include <Arduino.h>

#include "Claw.h"
#include "Constants.h"
#include "Lidar.h"
#include "Motor.h"
#include "PID.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "Sonar.h"
#include "Utils.h"

#include "States/State.h"
#include "States/State1.h"
#include "States/State2.h"

// OBJECT CREATION //
Motor motorL(MOTOR_LEFT_F_PIN, MOTOR_LEFT_B_PIN, Side::LEFT); 
Motor motorR(MOTOR_RIGHT_F_PIN, MOTOR_RIGHT_B_PIN, Side::RIGHT); 
PID pid(motorL, motorR);

Sonar sonar(TRIG_PIN, ECHO_PIN);

ServoESP servoLidarLeft(SERVO_LIDAR_LEFT_PIN, Name::LIDAR_LEFT, 90); //CHANGE CHASSIS_ZERO
ServoESP servoLidarRight(SERVO_LIDAR_RIGHT_PIN, Name::LIDAR_RIGHT, 100);

Lidar lidarLeft(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_LEFT, 0X2A, servoLidarLeft);
Lidar lidarRight(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_RIGHT, 0x2B, servoLidarRight);

Utils utils;

// STATE CREATION (Reverse Chronological) //
// State3 state3();
// State2 state2(&state3, &pid, &lidarRight);
// State1 state1(&state2);

// State* currentState = &state1;

void setup() {
    Serial.begin(115200);

    // INITIALIZATION //
    // utils.beginWire();
    utils.initializePins();

    // lidarLeft.initialiseLidar();
    // lidarRight.initialiseLidar();

    // HOMING //
    // servoLidarLeft.moveServoChassis(0);
    // servoLidarRight.moveServoChassis(0);
    
    // claw.home()'
}

void loop() { 
    // pid.usePID();
    motorL.setSpeed(1400, Direction::FORWARD);
    motorR.setSpeed(1400, Direction::FORWARD);
    // currentState->execute();
    // currentState = currentState->getNextState();
}