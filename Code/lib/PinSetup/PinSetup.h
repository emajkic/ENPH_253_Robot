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

// I2C Communication //
const int SDA_LIDAR = 21; // Lidars: 21, 22
const int SCL_LIDAR= 22;
const int SDA_EXTRA = 13; // OLED, Sonar: 37, 38
const int SCL_EXTRA = 14;

// Lidar //
const int XSHUT_PIN_LEFT = 8;
const int XSHUT_PIN_RIGHT = 7;

const int SERVO_LIDAR_LEFT_PIN = 9;
const int SERVO_LIDAR_RIGHT_PIN = 10;

// Reflectance Circuit //
const int QRD_PIN_LEFT = 3;
const int QRD_PIN_RIGHT = 1; 

// Hall Effect //
const int HALL_OUTPUT_PIN = 0;

// Motor Control - H-Bridges //
const int MOTOR_LEFT_F_PIN = 32;
const int MOTOR_LEFT_B_PIN = 33;
const int MOTOR_RIGHT_F_PIN = 25;
const int MOTOR_RIGHT_B_PIN = 26;

// Claw //
const int CLAW_SERVO_1_PIN = 12;
const int CLAW_SERVO_2_PIN = 38;
const int ROTARY_IN_CLK_PIN = 36;
const int ROTARY_IN_DT_PIN = 39;
const int CLAW_HOME_SWITCH_PIN = 15;

const int ROTARY_MOTOR_PIN = 37;
const int CLAMP_MOTOR_FORW_PIN = 4;
const int CLAMP_MOTOR_BACK_PIN = 2;

// Basket //
const int BASKET_SWITCH_PIN = 20;
const int PULLEY_MOTOR_1_PIN = 34;
const int PULLEY_MOTOR_2_PIN = 35;

#endif