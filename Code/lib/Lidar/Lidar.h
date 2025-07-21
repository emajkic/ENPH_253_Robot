#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>
#include <VL53L1X.h>
#include <map> // Required header for std::map

#include "ServoESP.h"
#include "Constants.h"
#include "PinSetup.h"

class Lidar
{
public:
    Lidar(int sclPin, int sdaPin, ServoESP& servo);
    
    /*
    * Initializes LiDAR sensor by starting I2C communication
    */
    bool initialiseLidar();

    /*
     * Stops measurements and the servos motion
     *
     * @param angle
     */
    bool stop();

private:
    VL53L1X sensor;
    ServoESP &servo;
    int sclPin;
    int sdaPin; // these are i2c enabled pins for communicating with the LiDAR

    uint16_t singleMeasurement(); 

    /*
     * Obtain distance reading array --> this should spin the servo
     */
    std::map<int, uint16_t> sweepReading(int endAngle);
};

#endif