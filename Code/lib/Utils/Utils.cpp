#include <Arduino.h>
#include <Wire.h>
#include <VL53L1X.h>

#include "Utils.h"
#include "PinSetup.h"
#include "Constants.h"

TwoWire lidarBus = TwoWire(0);      // VL53L1X on GPIO21/22
TwoWire displayBus = TwoWire(1);    // OLED + Sonar on GPIO37/38

const uint8_t sensorCount = 2;
const uint8_t xshutPins[sensorCount] = {XSHUT_PIN_LEFT, XSHUT_PIN_RIGHT};
VL53L1X sensors[sensorCount];

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
    // Lidar addresses //
    initLidar();

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

void Utils::initLidar() {
    for (int i = 0; i < 2; i++) {
        pinMode(xshutPins[i], OUTPUT);
        digitalWrite(xshutPins[i], LOW);
    }

    delay(10);    

    for (int i = 0; i < 2; i++) {
        pinMode(xshutPins[i], INPUT);  // Let sensor boot up
        delay(10);

        sensors[i].setBus(&lidarBus);
        sensors[i].setTimeout(500);
        if (!sensors[i].init()) {
            Serial.print("Lidar "); Serial.print(i); Serial.println(" failed to init");
            while (1);
        }

        sensors[i].setAddress(0x2A + i);  // Assign unique address
        sensors[i].startContinuous(50);
  }
}