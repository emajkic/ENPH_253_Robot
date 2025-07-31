#ifndef Lidar_h
#define Lidar_h

#include <Arduino.h>
#include <VL53L1X.h>
#include <map> // Required header for std::map

#include "ServoESP.h"
#include "Constants.h"
#include "PinSetup.h"


class Lidar {
public:
    Lidar(int sdaPin, int sclPin, int xshutPin, uint8_t i2cAddress, ServoESP &servo);

    bool initialiseLidar();
    bool stop();
    double petSearchRegular();
    double petSearchWindow();

    void sweepReading(int startAngle, int endAngle, int (&readings)[READING_LENGTH]);

    bool isPetInFront(int (&readings)[READING_LENGTH]);

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
    void removeOutliers(int avg, int (&distances)[READING_LENGTH]);

    bool centralFlatSection(int (&distances)[READING_LENGTH]);
    bool isIncreasing(int (&array)[READING_LENGTH], int dipTolerance, int overallThreshold, int startIndex, int endIndex);
    bool isDecreasing(int (&array)[READING_LENGTH], int bumpTolerance, int overallThreshold, int startIndex, int endIndex);

    // takes avg of section of array from startIndex to endIndex, both inclusive 
    // max endIndex = READING_LENGTH - 1
    int getAvg(int (&array)[READING_LENGTH], int startIndex, int endIndex);
};

#endif