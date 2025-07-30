#include <Arduino.h>
#include "driver/ledc.h"

#include "Claw.h"
#include "Constants.h"
#include "Diagnostics.h"
#include "Lidar.h"
#include "StateManager.h"
#include "Motor.h"
#include "PID.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "Utils.h"

// // OBJECT CREATION //
// StateManager stateManager;

Motor motorL(MOTOR_LEFT_F_PIN, MOTOR_LEFT_B_PIN, Side::LEFT); 
Motor motorR(MOTOR_RIGHT_F_PIN, MOTOR_RIGHT_B_PIN, Side::RIGHT); 
PID pid(motorL, motorR);

ServoESP servoLidarLeft(SERVO_LIDAR_LEFT_PIN, Name::LIDAR_LEFT, 90); //CHANGE CHASSIS_ZERO
ServoESP servoLidarRight(SERVO_LIDAR_RIGHT_PIN, Name::LIDAR_RIGHT, 100);

Lidar lidarLeft(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_LEFT, 0X2A, servoLidarLeft);
Lidar lidarRight(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_RIGHT, 0x2B, servoLidarRight);

Utils utils;

void setup() {
    Serial.begin(115200);
    // INITIALIZATION //
    utils.beginWire();
    utils.initializePins();

    lidarLeft.initialiseLidar();
    // lidarRight.initialiseLidar();

    servoLidarLeft.moveServoChassis(0);
    // servoLidarRight.moveServoChassis(0);
}

void loop() { 
    // pid.usePID(); 
    if (lidarLeft.petSearchRegular() != 0) {
        Serial.println("Pet on LEFT");
    }  else {
        Serial.println("No pet");
    }
    
    // if (lidarRight.petSearchRegular() != 0) {
    //     Serial.println("Pet on RIGHT");
    // }

    // stateManager.poll(); // Timing loops??? Helper/Minion?
}