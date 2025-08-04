#ifndef Constants_h
#define Constants_h

#include <Arduino.h>

// Speed Settings //
const int BASE_SPEED_L = 1400;  
const int BASE_SPEED_R = 1400;
const int MAX_SPEED = 4000;
const int MIN_SPEED = 1000;

// PID //
const int LINE_BLACK = 1;
const int LINE_WHITE = 0;

const int KP_LINE_FOLLOWER = 750;
const int KI_LINE_FOLLOWER = 0;
const int KD_LINE_FOLLOWER = 80;

// ServoESP //
const int SERVO_FREQ = 50;       // 50 Hz = 20 ms period (standard for servos)
const int SERVO_RESOLUTION = 12; // 12-bit resolution (0–4096)

// Sonar //
const int SONAR_BASE_DIST = 23; // [mm] CHECK THIS ******************************* --> checked just need to verify with actual chassis
const int SONAR_RAMP_INCREASE = 2; // [mm] CHECK THIS ******************************* --> checked just need to verify with actual chassis
const int SONAR_DEBRIS_INCREASE = 5; // [mm] CHECK THIS ******************************* --> checked just need to verify with actual chassis

// Claw //
const int Y_SHORT_PET = 5;
const int Y_TALL_PET = 20; //check
const int THETA_RIGHT_PET = 24;
const int THETA_LEFT_PET = 72; //CHECKKK

const int X_BASKET = 10; 
const int Y_BASKET = 10; // [cm] measure on chassis ******************************** !!!!!!!! **************
const int THETA_BASKET = 0; 

const int X_ARCHWAY = 0;
const int Y_ARCHWAY = 0;
const int THETA_ARCHWAY = 0;

const int X_RAMP = 33;
const int Y_RAMP = 10; 
const int THETA_RAMP = 72;

const int X_WINDOW = 32;
const int Y_WINDOW = 1; 
const int THETA_WINDOW = 50; // THIS IS A PLACEHOLDER

const int L1 = 18;
const int L2 = 19; // [cm] these are not final ******************************** !!!!!!!! **************

const double GEAR_RATIO = 1.5; 

const double ALPHA_0 = (180 - 21.7)* PI / 180; // angle of arm controlled by servo 1 relative to the horizontal [rad]
const double BETA_0 = 21.7 * PI / 180; // angle of arm controlled by servo 2 relative to servo 1's zero angle 

const double HALL_MIDPOINT = 4096 * 2 / 3.3; // because the midpoint moved to 2 --> check with acc circuit that this is consistent behaviour 
const double HALL_THRESHOLD = 4096 * 1 / 3.3; 

const int HALL_SWEEP_LENGTH = 6; // change this in testing --> feels reasonable to me now (this means move 3 clicks in either dir) 

// Continuous Servo // 
const int SERVO_CONT_FREQ = 250;
const int SERVO_CONT_RESOLUTION = 8;

// Lidar, Pet Search //
const double ANGULAR_RANGE_WINDOW = 0; // [degrees] ******************************** !!!!!!!! **************

const long TIMEOUT = 1000;   // [ms]
const long TIMEOUT_LIDAR = 1000; // [ms]
const int ANGULAR_STEP = 1; // [degrees]

// Constants for tuning lidar algorithm //
const float MAX_PET_DISTANCE = 400.0; // [mm]
const float MIN_PET_DISTANCE = 80.0; // [mm]

const int OUTLIER_THRESHOLD = 100; // [mm]

const int FLAT_SECTION_LENGTH = 10;
const int FLAT_SECTION_VARIATION = 30; // [mm]

const int MAX_SPIKE = 100; // [mm]

const int BUMP_TOLERANCE = 50; // [mm]
const int DIP_TOLERANCE = 30; // [mm]

const int DECREASE_THRESHOLD = 2; // [mm]
const int INCREASE_THRESHOLD = 2; // [mm]

const int READING_LENGTH = 40; // [entries or degrees of servo rotation]

#endif