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

ServoContinuous thetaMotor(CONT_SERVO_PIN); 

Claw claw(claw1Servo, claw2Servo, clampServo, thetaMotor); 


Lidar lidarLeft(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_LEFT, 0X2A, servoLidarLeft);
Lidar lidarRight(SDA_LIDAR, SCL_LIDAR, XSHUT_PIN_RIGHT, 0x2B, servoLidarRight);

Utils utils;

// STATE CREATION (Reverse Chronological) //
State4 state4;
State3 state3(&state4, &claw, &lidarRight);
State2 state2(&state3, &claw, &pid, &lidarRight, &motorL, &motorR);
State1 state1(&state2);

State* currentState = &state1;

unsigned long lastmotorswitch = millis();
int lastleft;
int lastright;

int currleft;
int currright;

Direction dir = Direction::FORWARD;

void setup() {
    Serial.begin(115200);

    // INITIALIZATION //
    utils.beginWire();
    utils.initializePins(); 

    //lidarLeft.initialiseLidar();
    //lidarRight.initialiseLidar();
=======
    motorL.setSpeed(1400, Direction::FORWARD);
    motorR.setSpeed(1400, Direction::FORWARD);

    // lidarLeft.initialiseLidar();
    // lidarRight.initialiseLidar();
>>>>>>> 3c4d0c4226b1f31d244153fd9434ed75cbd75ae4

    // HOMING //
    //servoLidarLeft.moveServoChassis(0);
    // servoLidarRight.moveServoChassis(0); 

    delay(1000); 

    claw.moveClaw(20,15,0); 

    delay(2000);

   claw.moveClaw(20,20,0); 

   delay(2000);

   claw.moveClaw(30,5,0); 
}

void loop() { 
    // pid.usePID();
    //motorL.setSpeed(1400, Direction::FORWARD);
    //motorR.setSpeed(1400, Direction::FORWARD);
=======
    // claw.home();
}

void loop() {
    pid.usePID();
    // unsigned long now = millis();

    // lastleft = currleft;
    // lastright = currright;

    // currleft = digitalRead(QRD_PIN_LEFT);
    // currright = digitalRead(QRD_PIN_RIGHT);

    // // Serial.print("(");
    // // Serial.print(currleft);
    // // Serial.print(", ");
    // // Serial.print(currright);
    // // Serial.println(")");

    // if (currleft == LOW && currright == LOW && lastleft == HIGH && lastright == HIGH) {
    //     Serial.println("Transition1");
    //     // Serial.print("(");
    //     // Serial.print(currleft);
    //     // Serial.print(", ");
    //     // Serial.print(currright);
    //     // Serial.println(")");
    // }

    // if (now - lastmotorswitch > 5000) {
    //     if (dir == Direction::FORWARD) {
    //         dir = Direction::BACKWARD;
    //         motorL.setSpeed(1400, Direction::BACKWARD);
    //         motorR.setSpeed(1400, Direction::BACKWARD);

    //     } else {
    //         dir = Direction::FORWARD;
    //         motorL.setSpeed(1400, Direction::FORWARD);
    //         motorR.setSpeed(1400, Direction::FORWARD);
    //     }
    //     lastmotorswitch = now;
    // }




    // if (lidarLeft.petSearchRegular() != 0) {
    //     motorL.stop();
    //     motorR.stop();
    //     delay(2000);
    // } else if (lidarRight.petSearchRegular() != 0) {
    //     motorL.stop();
    //     motorR.stop();
    //     delay(2000);
    // }   

>>>>>>> 3c4d0c4226b1f31d244153fd9434ed75cbd75ae4
    // currentState->execute();
    // currentState = currentState->getNextState();

    // int dist = sonar.getDistance(); 
    // Serial.println(dist); 
    
    // Serial.println(sonar.debrisDetected());

   // Serial.println(lidarLeft.petSearchPillar()); 
   //servoLidarLeft.moveServoChassis(0); 

}
