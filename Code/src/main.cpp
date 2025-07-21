#include <Arduino.h>

#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"
#include "Diagnostics.h"

Motor motorL(MOTOR_LEFT_F_PIN, MOTOR_LEFT_B_PIN, Side::LEFT); //forward, backward
Motor motorR(MOTOR_RIGHT_F_PIN, MOTOR_RIGHT_B_PIN, Side::RIGHT); //forward, backward

PID pid(motorL, motorR);

// Diagnostics diagnostics;

void setup() {
    motorL.setSpeed(BASE_SPEED_L, Direction::FORWARD);
    motorR.setSpeed(BASE_SPEED_R, Direction::FORWARD);

    // diagnostics.init();
}

void loop() { 
    pid.usePID();
    //diagnostics.runSimple();
}

