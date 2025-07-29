#include <Arduino.h>
#include <VL53L1X.h>
#include <Wire.h>
#include <map> // Required header for std::map

#include "ServoESP.h"
#include "Lidar.h"
#include "Constants.h"
#include "PinSetup.h"

Lidar::Lidar(int sdaPin, int sclPin, int xshutPin, uint8_t i2cAddress, ServoESP &servo)
    : sclPin(sclPin), sdaPin(sdaPin), xshutPin(xshutPin), address(i2cAddress), servo(servo)
{
    servo.attach();
}

/*
 * Sweep the servo within angular range, at each point saving distance reading to obtain map with angle
 *
 * @return map with key = angle of servo, value = distance reading taken at that point pairs
 */
std::map<int, uint16_t> Lidar::sweepReading(int startAngle, int endAngle)
{
    std::map<int, uint16_t> readings;

    for (int angle = startAngle; angle <= endAngle; angle += ANGULAR_STEP)
    {
        this->servo.moveServoChassis(angle);
        uint16_t reading = singleMeasurement();
        readings.insert({angle, reading});
    }

    return readings; 
}

/*
 * Stops measurements and the servos motion
 *
 * @return true if successful stop
 */
bool Lidar::stop() {
    servo.moveServoChassis(0); 
    servo.detach();  // Or your stop logic
    return true;
}

/*
* Scan angular range to find where to stop moving for pet retreival
*
* @return 0 if no pet is found or chassis not positioned at correct distance to stop and retrieve
*/
double Lidar::petSearchRegular() {
    double distance = 0.0;

    std::map<int, uint16_t> sweepReadings = sweepReading(-20, 20);
    
    return distance;
}

/*
* //TODO : Come up with spec, implement
*
* @return 
*/
double Lidar::petSearchWindow() {
    return 0.0;
}

/* 
* Initialize LiDAR I2C communication
*
* @return false if timed out 
*/
bool Lidar::initialiseLidar(){
    pinMode(xshutPin, OUTPUT);
    digitalWrite(xshutPin, LOW);
    delay(10);

    pinMode(xshutPin, INPUT);
    delay(10);  // Let sensor boot

    sensor.setTimeout(500);

    unsigned long start = millis();
    while (!sensor.init()) {
        delay(50);
        if (millis() - start > TIMEOUT_LIDAR){
            return false;
        }
    }

    sensor.setAddress(address);

    sensor.setDistanceMode(VL53L1X::Short);
    sensor.setMeasurementTimingBudget(20000);

    return true;
}

/*
* Take a single distance measurement with sensor
*
* @return uint containing the measurement, if failed it returns 0 **choose different value***
*/
uint16_t Lidar::singleMeasurement()
{
    sensor.readSingle(false); // false means non-blocking

    unsigned long start = millis();

    while (!sensor.dataReady())
    { // wait until measurement ready
        // do other stuff --> to be determined based on needs later in the project
        if (millis() - start > TIMEOUT)
        {
            return 0; 
        }
    }

    return sensor.read(false); // return value
}