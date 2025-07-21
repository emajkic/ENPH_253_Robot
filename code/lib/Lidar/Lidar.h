#ifndef LIDAR_H
#define LIDAR_H

#include <Arduino.h>
#include <ServoESP.h>
#include <VL53L1X.h>

// Data structure inclusions: 
#include <map> // Required header for std::map

class Lidar
{
public:
    Lidar(int sclPin, int sdaPin, ServoESP& servo);

    /*
     * Obtain distance reading array --> this should spin the servo
     */
    std::map<int, uint16_t> sweepReading(int endAngle);

    /*
     * Stops measurements and the servos motion
     *
     * @param angle
     */
    bool stop();

    /*
    * 
    */
    bool initialiseLidar();

private:
    VL53L1X sensor;
    ServoESP &servo;
    int sclPin;
    int sdaPin; // these are i2c enabled pins for communicating with the LiDAR

    uint16_t singleMeasurement(); 
};

#endif