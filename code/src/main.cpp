#include <Arduino.h>
#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"

Motor motorL(7, 8, Side::LEFT); //forward, backward
Motor motorR(2, 4, Side::RIGHT); //forward, backward

PID pid(PIDType::LineFollower, motorL, motorR);

void printSpeeds();

void setup() {
    Serial.begin(9600);
    motorL.setSpeed(1700, Direction::FORWARD);
    motorR.setSpeed(1850, Direction::FORWARD);
}

void loop() {    
    pid.usePID();
    delay(10);
}

void printSpeeds() {
    Serial.print("L: ");
    int sL = motorL.getSpeed();
    Serial.println(sL);

    Serial.print("R: ");
    int sR = motorR.getSpeed();
    Serial.println(sR);
}
