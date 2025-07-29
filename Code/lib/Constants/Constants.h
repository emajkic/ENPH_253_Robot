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

const int KP_LINE_FOLLOWER = 120;
const int KI_LINE_FOLLOWER = 0;
const int KD_LINE_FOLLOWER = 90;


// ServoESP //
const int servoFreq = 50;       // 50 Hz = 20 ms period (standard for servos)
const int servoResolution = 12; // 12-bit resolution (0–4096)

// Claw //
const int xbasket = 10; 
const int ybasket = 10; // [cm] measure on chassis ******************************** !!!!!!!! **************
const int thetaBasket = 270; 

const int l1 = 18;
const int l2 = 19; // [cm] these are not final ******************************** !!!!!!!! **************

const double alphaO = 1.68879093374; // angle of arm controlled by servo 1 relative to the horizontal [rad]
const double betaO = 0.942477796077;

const double HALL_BASE_SIGNAL = 1.6; // [V]

// Lidar, Pet Search //
const double MIN_PET_DIST = 15.0; // [cm] these are not final ******************************** !!!!!!!! **************
const double MAX_PET_DIST = 30.0; // [cm]
const double ANGULAR_RANGE_PET = 40; // [degrees]
const double ANGULAR_RANGE_WINDOW = 0; // [degrees] ******************************** !!!!!!!! **************

const long TIMEOUT = 1000;   // [ms]
const long TIMEOUT_LIDAR = 1000; // [ms]
const int ANGULAR_STEP = 1; // [degrees]

// ALGO CONSTANTS

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