#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>

#include "Utils.h"
#include "PinSetup.h"
#include "Constants.h"

TwoWire displayBus = TwoWire(1);    // OLED + Sonar on GPIO13/14

/*
* Begin I2C wire communication (*call before initializePins)
*/
void Utils::beginWire() {
    Wire.begin(SDA_LIDAR, SCL_LIDAR);
    Wire.setClock(400000);

    displayBus.begin(SDA_EXTRA, SCL_EXTRA);
    displayBus.setClock(400000);
}

/*
* Call pinMode for all pins defined in PinSetup.h
*/
void Utils::initializePins() { 
    // On //
    pinMode(ON_PIN, INPUT_PULLUP);

    // Reflectance Circuit //
    pinMode(QRD_PIN_LEFT, INPUT);
    pinMode(QRD_PIN_RIGHT, INPUT);

    // Hall Effect //
    pinMode(HALL_OUTPUT_PIN, INPUT_PULLUP);

    // Claw //
    pinMode(ROTARY_IN_CLK_PIN, INPUT_PULLUP);
    pinMode(ROTARY_IN_DT_PIN, INPUT_PULLUP);
    pinMode(CLAW_HOME_SWITCH_PIN, INPUT_PULLUP);

    // Basket //
    pinMode(PULLEY_MOTOR_1_PIN, OUTPUT);
    pinMode(PULLEY_MOTOR_2_PIN, OUTPUT);
    pinMode(BASKET_SWITCH_PIN, INPUT_PULLUP);
}