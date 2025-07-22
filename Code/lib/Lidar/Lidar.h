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
    Lidar(int sdaPin, int sclPin, int xshutPin, uint8_t i2cAddress, ServoESP &servo);
    
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

    /*
    * Scan angular range to find where to stop moving for pet retreival
    *
    * @return 0 if no pet is found or chassis not positioned at correct distance to stop and retrieve
    */
    double petSearchRegular();

    /*
    * //TODO : Come up with spec, implement
    *
    * @return 
    */
    double petSearchWindow();

    /*
     * Obtain distance reading array --> this should spin the servo
     */
    std::map<int, uint16_t> sweepReading(int startAngle, int endAngle);

private:
    VL53L1X sensor;
    ServoESP &servo;
    int sclPin;
    int sdaPin; 
    int xshutPin;
    uint8_t address;

    uint16_t singleMeasurement(); 
};

#endif