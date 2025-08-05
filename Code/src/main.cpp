#include <Arduino.h>

#include "Claw.h"
#include "Constants.h"
#include "Lidar.h"
#include "Motor.h"
#include "PID.h"
#include "PinSetup.h"
#include "ServoContinuous.h"
#include "ServoESP.h"
#include "Sonar.h"
#include "Utils.h"

#include "States/State.h"
#include "States/State1.h"
#include "States/State2.h"
#include "States/State3.h"
#include "States/State4.h"
#include "States/State5.h"
#include "States/State6.h"
#include "States/State7.h"
#include "States/State8.h"
#include "States/State9.h"
// #include "States/State10.h"

// OBJECT CREATION //
Motor motorL(MOTOR_LEFT_F_PIN, MOTOR_LEFT_B_PIN, Side::LEFT); 
Motor motorR(MOTOR_RIGHT_F_PIN, MOTOR_RIGHT_B_PIN, Side::RIGHT); 
PID pid(motorL, motorR);

ServoESP clawServo1(CLAW_SERVO_1_PIN, Name::CLAW1, 0);
ServoESP clawServo2(CLAW_SERVO_2_PIN, Name::CLAW2, 0);
ServoESP clawClampServo(CLAMP_SERVO_PIN, Name::CLAMP, 0);
ServoContinuous thetaMotor(CONT_SERVO_PIN);
Claw claw(clawServo1, clawServo2, clawClampServo, thetaMotor);

Sonar sonar(TRIG_PIN, ECHO_PIN);

ServoESP servoLidarLeft(SERVO_LIDAR_LEFT_PIN, Name::LIDAR_LEFT, 90); //CHANGE CHASSIS_ZERO
ServoESP servoLidarRight(SERVO_LIDAR_RIGHT_PIN, Name::LIDAR_RIGHT, 100);

ServoESP claw1Servo(CLAW_SERVO_1_PIN, Name::CLAW1, 0); 
ServoESP claw2Servo(CLAW_SERVO_2_PIN, Name::CLAW2, 0); 
ServoESP clampServo(CLAMP_SERVO_PIN, Name::CLAMP, 0); 

Lidar lidarLeft(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_LEFT, 0X2A, servoLidarLeft);
Lidar lidarRight(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_RIGHT, 0x2B, servoLidarRight);

Utils utils;

// STATE CREATION (Reverse Chronological) //
State9 state9;
State8 state8(&state9, &pid, &lidarLeft, &motorL, &motorR, &claw);
State7 state7(&state8, &claw);
State6 state6(&state7, &pid, &lidarLeft, &claw, &motorL, &motorR);
State5 state5(&state6, &pid, &claw, &sonar);
State4 state4(&state5, &pid, &sonar);
State3 state3(&state4, &claw);
State2 state2(&state3, &claw, &pid, &lidarRight, &motorL, &motorR);
State1 state1(&state2);

State* currentState = &state2; // Skip state1 idle state

void setup() {
    Serial.begin(115200);

    // INITIALIZATION //
    utils.beginWire();
    utils.initializePins();

    // lidarLeft.initialiseLidar();
    // lidarRight.initialiseLidar();

    // HOMING //
    // servoLidarLeft.moveServoChassis(0);
    // servoLidarRight.moveServoChassis(0); 

    // claw.homeTheta();
    // claw.homeXY();
    // claw.unclamp();
    // claw.archwayPosition();
}

void loop() {
    pid.usePID(BASE_SPEED);
    // currentState->execute();
    // currentState = currentState->getNextState();
}
