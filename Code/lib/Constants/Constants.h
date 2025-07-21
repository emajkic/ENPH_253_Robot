#ifndef Constants_h
#define Constants_h

// Motors //
const int MIN_SPEED = 800;
const int MAX_SPEED = 4095;

const int BASE_SPEED_L = 1200;
const int BASE_SPEED_R = 1200;

// PID //
const int LINE_BLACK = 1;
const int LINE_WHITE = 0;

const int KP_LINE_FOLLOWER = 55;
const int KI_LINE_FOLLOWER = 0;
const int KD_LINE_FOLLOWER = 0;

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

const double HALL_BASE_SIGNAL = 1.6; //[V]

#endif