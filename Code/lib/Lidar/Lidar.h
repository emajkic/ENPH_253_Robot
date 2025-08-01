#ifndef Lidar_h
#define Lidar_h

#include <Arduino.h>
#include <VL53L1X.h>

#include "ServoESP.h"
#include "Constants.h"
#include "PinSetup.h"


class Lidar {
public:
    Lidar(int sdaPin, int sclPin, int xshutPin, uint8_t i2cAddress, ServoESP &servo);

    /*
    * Initialises the lidar sensor, including: 
    * - pinModes for the xshuts, address, distance mode, and timing budget setting
    * - the attaching for the servo occurs in the constructor
    * 
    * @return true if successfully initialised 
    */
    bool initialiseLidar();

    /*
    * Stops the lidar's associated servo and detaches it from it's pwm channel
    *
    * @return true if successfully stopped
    */
    bool stop();

    /*
    * Searches for all pets aside from the window; this makes the servo sweep, take in the lidar reading, and check if it is a pet
    * 
    * @return the distance to the pet, but if no pet found, return 0.0
    */
    double petSearchRegular();

    /*
    * Searches for the window pet 
    */
    double petSearchWindow();

    /*
    * Sweeps the servo while the lidar takes readings at each angular position, with the readings recorded in the array passed in
    *
    * @param startangle     the angle at which to start the lidar's sweep (relative to chassisZero)
    * @param endangle       the angle at which to end the lidar's sweep (relative to chassisZero)
    * @param readings       the array in which to store the readings 
    */
    void sweepReading(int startAngle, int endAngle, int (&readings)[READING_LENGTH]);

private:
    VL53L1X sensor;
    ServoESP &servo;
    int sclPin;
    int sdaPin;
    int xshutPin;
    uint8_t address;

    uint16_t singleMeasurement();

    void medianFilter(const int (&raw)[READING_LENGTH], int (&filtered)[READING_LENGTH]);
    void clampSpikes(int (&data)[READING_LENGTH], int maxStep = 100);
    int getAvg(int (&array)[READING_LENGTH], int startIndex, int endIndex);
    void removeOutliers(int avg, int (&distances)[READING_LENGTH]);

    bool centralFlatSection(int (&distances)[READING_LENGTH]);
    bool isIncreasing(int (&array)[READING_LENGTH], int dipTolerance, int overallThreshold, int startIndex, int endIndex);
    bool isDecreasing(int (&array)[READING_LENGTH], int bumpTolerance, int overallThreshold, int startIndex, int endIndex);
    
    bool isPetInFront(int (&readings)[READING_LENGTH]);
};

#endif