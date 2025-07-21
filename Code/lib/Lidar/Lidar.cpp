#include <Arduino.h>
#include <VL53L1X.h>
#include <Wire.h>
#include <map> // Required header for std::map

#include "ServoESP.h"
#include "Lidar.h"
#include "Constants.h"
#include "PinSetup.h"

unsigned long timeout = 1000;   // val in ms (check this)
unsigned long timeoutLidar = 1000; 
const int angularStep = 1; // val in degrees

Lidar::Lidar(int sdaPin, int sclPin, ServoESP &servo) : sclPin(sclPin), sdaPin(sdaPin), servo(servo)
{ 
    // servo obj initialisation
    servo.attach();
    //servo.moveServo(0); 
}

/*
 * Sweep the servo from 0-180, at each point saving distance reading to obtain map with angle --> distance to serve as the robot's vision
 *
 * @return map with key = angle of servo, value = distance reading taken at that point
 *
 * the angle increments in steps of size controlled by constants above (AND LATER IN CONSTANTS.H)
 */
std::map<int, uint16_t> Lidar::sweepReading(int endAngle)
{
    std::map<int, uint16_t> readings;

    for (int angle = 0; angle <= endAngle; angle += angularStep)
    {
        this->servo.moveServo(angle);
        uint16_t reading = singleMeasurement();
        readings.insert({angle, reading});
    }

   //servo.moveServo(0); 

    return readings; 
}

/*
 * Stops measurements and the servos motion
 *
 */
bool Lidar::stop() {
    servo.moveServo(0); 
    servo.detach();  // Or your stop logic
    return true;
}

/* returns false if timed out */
bool Lidar::initialiseLidar()
{
    unsigned long start = millis(); 

    sensor.setTimeout(200); // setting to min timeout for short mode; not giving us the ability to use any others bc its the most resistant to ambient light AND it has a 1.3m sensing range, which is more than enough
    while (!sensor.init())
    {
       if (millis() - start > timeoutLidar){
            return false; 
       } 
    }

    // Minimum timing budget is 20 ms for short distance mode and 33 ms for
    // medium and long distance modes. See the VL53L1X datasheet for more
    // information on range and timing limits.
    sensor.setDistanceMode(VL53L1X::Short);
    sensor.setMeasurementTimingBudget(20000);

    return true; 
}

/*
this returns a uint containing the measurement, if failed it returns 0 **choose different value*** --> exceptions are apparently terrible for esps
*/
uint16_t Lidar::singleMeasurement()
{
    sensor.readSingle(false); // false means non-blocking

    unsigned long start = millis();

    while (!sensor.dataReady())
    { // wait until measurement ready
        // do other stuff --> to be determined based on needs later in the project
        if (millis() - start > timeout)
        {
            return 0; 
        }
        
    }

    return sensor.read(false); // return value
}

