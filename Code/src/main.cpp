#include <Arduino.h>

#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"
#include "Diagnostics.h"

Motor motorL(2, 4, Side::LEFT); //forward, backward
Motor motorR(26, 25, Side::RIGHT); //forward, backward

PID pid(motorL, motorR);

// Diagnostics diagnostics;

void setup() {
    motorL.setSpeed(BASE_SPEED_L, Direction::FORWARD);
    motorR.setSpeed(BASE_SPEED_R, Direction::FORWARD);

    // diagnostics.init();
}

void loop() { 
    pid.usePID();
    // int leftReading = digitalRead(12);
    // int rightReading = digitalRead(14);

    // if (count = 2000) {
    //     // Serial.print("Error: ");
    //     // Serial.println(pid.getError());

    //     Serial.print("Left read: ");
    //     Serial.println(leftReading);

    //     Serial.print("Right read: ");
    //     Serial.println(rightReading);
    //     count = 0;
    // }

    // count++;
    //diagnostics.runSimple();
}

