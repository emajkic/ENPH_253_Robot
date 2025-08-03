#ifndef PinSetup_h
#define PinSetup_h

#include <Arduino.h>

// PWM Channels //
const int pwmChannelFL = 0;
const int pwmChannelBL = 1;
const int pwmChannelFR = 2;
const int pwmChannelBR = 3;
const int pwmChannelC1 = 4;
const int pwmChannelC2 = 5;
const int pwmChannelLL = 6;
const int pwmChannelLR = 7;
const int pwmChannelClamp = 8;
const int pwmChannelContServo = 9;

// Start //
const int ON_PIN = 37;

// I2C Communication //
const int SDA_LIDAR = 21; // Lidars: 21, 22
const int SCL_LIDAR= 22;
const int TRIG_PIN = 19; // Sonar
const int ECHO_PIN = 20;

// Lidar //
const int XSHUT_PIN_LEFT = 7;
const int XSHUT_PIN_RIGHT = 8;

const int SERVO_LIDAR_LEFT_PIN = 9;
const int SERVO_LIDAR_RIGHT_PIN = 10;

// Reflectance Circuit //
const int QRD_PIN_LEFT = 34; 
const int QRD_PIN_RIGHT = 35; 

// Hall Effect //
const int HALL_OUTPUT_PIN = 38;

// Motor Control - H-Bridges //
const int MOTOR_LEFT_F_PIN = 32;
const int MOTOR_LEFT_B_PIN = 33;
const int MOTOR_RIGHT_F_PIN = 25;
const int MOTOR_RIGHT_B_PIN = 26;

// Claw //
const int CLAW_SERVO_1_PIN = 27;
const int CLAW_SERVO_2_PIN = 0;
const int ROTARY_IN_CLK_PIN = 36;
const int ROTARY_IN_DT_PIN = 39;
const int CLAW_HOME_SWITCH_PIN = 4;

const int CONT_SERVO_PIN = 12; // "Rotary Motor"
const int CLAMP_SERVO_PIN = 15;

// Basket //
const int BASKET_SWITCH_PIN = 13;
const int PULLEY_MOTOR_1_PIN = 14;
const int PULLEY_MOTOR_2_PIN = 14;

#endif