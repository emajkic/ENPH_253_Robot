#include <Arduino.h>

#include "Utils.h"
#include "PinSetup.h"
#include "Constants.h"

/*
* Call pinMode for all pins defined in PinSetup.h
*/
void Utils::initializePins() {
    pinMode(QRD_PIN_LEFT, INPUT);
    pinMode(QRD_PIN_RIGHT, INPUT); //etc
}