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

const int KP_COMPASS_FOLLOWER = 0;
const int KI_COMPASS_FOLLOWER = 0;
const int KD_COMPASS_FOLLOWER = 0;

// Magnetometer //
const int REF_ANGLE_DEBRIS_1 = 45; // Change names to describe debris
const int REF_ANGLE_DEBRIS_2 = 45;

#endif