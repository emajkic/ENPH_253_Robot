#include <Arduino.h>

// #include "Claw.h"
#include "Constants.h"
// #include "Diagnostics.h"
#include "Lidar.h"
#include "Motor.h"
#include "PID.h"
#include "PinSetup.h"
#include "ServoESP.h"
#include "Utils.h"

// // OBJECT CREATION //
Motor motorL(MOTOR_LEFT_F_PIN, MOTOR_LEFT_B_PIN, Side::LEFT); //forward, backward
Motor motorR(MOTOR_RIGHT_F_PIN, MOTOR_RIGHT_B_PIN, Side::RIGHT); //forward, backward
PID pid(motorL, motorR);

// ServoESP servoLidarLeft(SERVO_LIDAR_LEFT_PIN, Name::LIDAR_LEFT, 92); //CHANGE CHASSIS_ZERO
// ServoESP servoLidarRight(SERVO_LIDAR_RIGHT_PIN, Name::LIDAR_RIGHT, 0);

// Lidar lidarLeft(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_LEFT, 0X2A, servoLidarLeft);
// Lidar lidarRight(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_RIGHT, 0x2B, servoLidarRight);

// Diagnostics diagnostics;
Utils utils;

void setup() {

    // Serial.begin(115200);
    // INITIALIZATION //
    // utils.beginWire();
    utils.initializePins();
    //lidarLeft.initialiseLidar();
    // diagnostics.init();

    motorR.setSpeed(BASE_SPEED_R, Direction::FORWARD);
    motorL.setSpeed(BASE_SPEED_L, Direction::FORWARD);

}

void loop() { 
    pid.usePID();
}






<<<<<<< HEAD
      

      Serial.println();
=======
>>>>>>> e5dcf6fda042238297ef54c13a392fc53bae65fd





// void printMap(std::map<int, uint16_t> map){
//   for (std::pair<int, uint16_t> element : map) {
//       Serial.print(element.first);
//       Serial.print(": ");
//       Serial.print(element.second);
//       Serial.println();
//   }
// }