#ifndef PinSetup_h
#define PinSetup_h

#include <Arduino.h>

/*
* Pin Definitions
*/

// PWM Channels //
const int pwmChannelFL = 0;
const int pwmChannelBL = 1;
const int pwmChannelFR = 2;
const int pwmChannelBR = 3;

// PID //
const int LEFT_QRD_PIN = 12;
const int RIGHT_QRD_PIN = 14;

// Magnetometer //
const int SCL_MAGNETO = 22;
const int SDA_MAGNETO = 21;


#endif