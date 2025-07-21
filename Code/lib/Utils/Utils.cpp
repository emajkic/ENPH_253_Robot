#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>

#include "Utils.h"
#include "PinSetup.h"
#include "Constants.h"

TwoWire lidarBus = TwoWire(0);      // VL53L1X on GPIO21/22
TwoWire displayBus = TwoWire(1);    // OLED + Sonar on GPIO37/38

/*
* Begin I2C wire communication (*call before initializePins)
*/
void Utils::beginWire() {
    lidarBus.begin(SDA_LIDAR, SCL_LIDAR);
    lidarBus.setClock(400000);

    displayBus.begin(SDA_EXTRA, SCL_EXTRA);
    displayBus.setClock(400000);
}

/*
* Call pinMode for all pins defined in PinSetup.h
*/
void Utils::initializePins() {
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
    pinMode(BASKET_SWITCH_PIN, INPUT_PULLUP);
}