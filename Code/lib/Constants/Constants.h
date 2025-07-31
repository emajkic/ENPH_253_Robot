#ifndef Constants_h
#define Constants_h

#include <Arduino.h>

// Speed Settings
const int BASE_SPEED_L = 1300;  
const int BASE_SPEED_R = 1300;
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

// Claw //
const int X_BASKET = 10; 
const int Y_BASKET = 10; // [cm] measure on chassis ******************************** !!!!!!!! **************
const int THETA_BASKET = 270; 

const int L1 = 18;
const int L2 = 19; // [cm] these are not final ******************************** !!!!!!!! **************

const double ALPHA_0 = 2.51327412287; // angle of arm controlled by servo 1 relative to the horizontal [rad]
const double BETA_0 = 0.692895713042;

const int X_ARCHWAY = 0;
const int Y_ARCHWAY = 0;
const int THETA_ARCHWAY = 0;

const double HALL_MIDPOINT = 4096 * 2 / 3.3; // because the midpoint moved to 2 --> check with acc circuit that this is consistent behaviour 
const double HALL_THRESHOLD = 4096 * 1 / 3.3;

// Lidar, Pet Search //
const double ANGULAR_RANGE_PET = 40; // [degrees]
const double ANGULAR_RANGE_WINDOW = 0; // [degrees] ******************************** !!!!!!!! **************

const long TIMEOUT = 1000;   // [ms]
const long TIMEOUT_LIDAR = 1000; // [ms]
const int ANGULAR_STEP = 1; // [degrees]

// ALGO CONSTANTS //
const float MAX_PET_DISTANCE = 400.0; // mm
const int OUTLIER_THRESHOLD = 100;

const int FLAT_SECTION_LENGTH = 10;
const int FLAT_SECTION_VARIATION = 30;

const int BUMP_TOLERANCE = 50;
const int DECREASE_THRESHOLD = 2;

const int DIP_TOLERANCE = 30;
const int INCREASE_THRESHOLD = 2;

const int READING_LENGTH = 40; 

#endif