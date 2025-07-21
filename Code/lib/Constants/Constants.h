#ifndef Constants_h
#define Constants_h

// Motors //
const int MIN_SPEED = 800;
const int MAX_SPEED = 4095;

const int BASE_SPEED_L = 1200;
const int BASE_SPEED_R = 1200; // should just have one base speed when motors same

// PID //
const int LINE_BLACK = 1;
const int LINE_WHITE = 0;

const int KP_LINE_FOLLOWER = 55;
const int KI_LINE_FOLLOWER = 0;
const int KD_LINE_FOLLOWER = 0;

// ServoESP //
const int servoFreq = 50;       // 50 Hz = 20 ms period (standard for servos)
const int servoResolution = 12; // 12-bit resolution (0–4096)

#endif