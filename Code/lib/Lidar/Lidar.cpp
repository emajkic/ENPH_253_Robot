#include <Arduino.h>
#include <VL53L1X.h>
#include <Wire.h>
#include <map> // Required header for std::map

#include "ServoESP.h"
#include "Constants.h"
#include "PinSetup.h"
#include "Lidar.h"

Lidar::Lidar(int sdaPin, int sclPin, int xshutPin, uint8_t i2cAddress, ServoESP &servo)
    : sclPin(sclPin), sdaPin(sdaPin), xshutPin(xshutPin), address(i2cAddress), servo(servo)
{
  servo.attach();
  risingEdgeCount = 0;
  previousDistance = 0;
}

/*
 * Initialises the lidar sensor, including:
 * - pinModes for the xshuts, address, distance mode, and timing budget setting
 * - the attaching for the servo occurs in the constructor
 *
 * @return true if successfully initialised
 */
bool Lidar::initialiseLidar()
{
  pinMode(xshutPin, OUTPUT);
  digitalWrite(xshutPin, LOW);
  delay(10);

  pinMode(xshutPin, INPUT);
  delay(10); // Let sensor boot

  sensor.setTimeout(500);

  unsigned long start = millis();
  while (!sensor.init())
  {
    delay(50);
    if (millis() - start > TIMEOUT_LIDAR)
    {
      return false;
    }
  }

  sensor.setAddress(address);

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(20000);

  return true;
}

/*
 * Stops the lidar's associated servo and detaches it from it's pwm channel
 *
 * @return true if successfully stopped
 */
bool Lidar::stop()
{
  servo.moveServoChassis(0);
  servo.detach();
  return true;
}

/*
 * Searches for all pets aside from the window; this makes the servo sweep, take in the lidar reading, and check if it is a pet
 *
 * @return the distance to the pet, but if no pet found, return 0.0
 */
double Lidar::petSearchRegular()
{
  double distance = 0.0;

  int readings[READING_LENGTH] = {};

  sweepReading(-READING_LENGTH / 2, READING_LENGTH / 2, readings);

  bool isPet = isPetInFront(readings);

  if (isPet)
  {
    distance = getAvg(readings, 15, 25); // was just readings[20] --> see if this is better
  }

  return distance;
}

/*
 * Searches for the window pet
 *
 * @return the distance to the pet, but if no pet found, return 0.0
 */
double Lidar::petSearchWindow()
{
  return 0.0;
}

/*
 * Searches for the pillar
 */
double Lidar::petSearchPillar()
{
  double distance = 0.0;

  int readings[READING_LENGTH] = {};

  sweepReading(-READING_LENGTH / 2, READING_LENGTH / 2, readings);

  bool isPet = isPillarInFront(readings);

  if (isPet)
  {
    distance = getAvg(readings, 15, 25); // was just readings[20] --> see if this is better
  }

  return distance;
}

/*
 * Sweeps the servo while the lidar takes readings at each angular position, with the readings recorded in the array passed in
 *
 * @param startangle     the angle at which to start the lidar's sweep (relative to chassisZero)
 * @param endangle       the angle at which to end the lidar's sweep (relative to chassisZero)
 * @param readings       the array in which to store the readings
 */
void Lidar::sweepReading(int startAngle, int endAngle, int (&readings)[READING_LENGTH])
{
  for (int angle = startAngle; angle <= endAngle; angle += ANGULAR_STEP)
  {
    this->servo.moveServoChassis(angle);
    //delay(50);
   uint16_t reading = singleMeasurement();
   readings[angle - startAngle] = reading;
  }
}

// ------ PRIVATE FUNCTIONS ------ //

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

void Lidar::medianFilter(const int (&raw)[READING_LENGTH], int (&filtered)[READING_LENGTH])
{
  for (int i = 0; i < READING_LENGTH; i++)
  {
    int window[5];

    for (int j = -2; j <= 2; j++)
    {
      int index = i + j;
      if (index < 0)
        index = 0;
      if (index >= READING_LENGTH)
        index = 39;
      window[j + 2] = raw[index];
    }

    std::sort(window, window + 5);
    filtered[i] = window[2];
  }
}

void Lidar::clampSpikes(int (&data)[READING_LENGTH], int maxStep)
{
  for (int i = 1; i < READING_LENGTH; i++)
  {
    int diff = data[i] - data[i - 1];
    if (abs(diff) > maxStep)
    {
      data[i] = data[i - 1] + (diff > 0 ? maxStep : -maxStep);
    }
  }
}

int Lidar::getAvg(int (&array)[READING_LENGTH], int startIndex, int endIndex)
{
  int sum = 0;
  for (int i = startIndex; i <= endIndex; i++)
  {
    sum += array[i];
  }
  // Serial.println(sum / (endIndex - startIndex + 1));
  return sum / (endIndex - startIndex + 1);
}

void Lidar::removeOutliers(int avg, int (&distances)[READING_LENGTH])
{
  for (int j = 0; j < READING_LENGTH; j++)
  {
    if (abs(distances[j] - avg) > OUTLIER_THRESHOLD)
    {
      if (j == 0)
      {
        distances[j] = avg;
      }
      else if (j == 39)
      {
        distances[j] = distances[j - 1];
      }
      else
      {
        distances[j] = (distances[j - 1] + distances[j + 1]) / 2;
      }
    }
  }
}

void Lidar::findMinAndLocation(int (&distances)[READING_LENGTH], int (&values)[2])
{
  int min = 2000;
  for (int i = 0; i < READING_LENGTH; i++)
  {
    if (distances[i] <= min && i < 30)
    {
      min = distances[i];

      values[0] = i;
      values[1] = min;
    }
    else if (distances[i] < min && i > 30)
    {
      values[0] = i;
      values[1] = min;
    } // make it such that the min position is the last occurrence in the array until 30, because if it appears after that it is likely a fluke
  }
}

bool Lidar::centralFlatSection(int (&distances)[READING_LENGTH])
{
  int refIndex = READING_LENGTH / 2 - FLAT_SECTION_LENGTH / 2;
  int reference = distances[refIndex];
  int sum = 0;

  for (int j = refIndex + 1; j < READING_LENGTH / 2 + FLAT_SECTION_LENGTH / 2; j++)
  {
    if (abs(distances[j] - reference) > FLAT_SECTION_VARIATION)
    {
      Serial.println("ending due to non-flat");
      return false;
    }
    sum += distances[j];
  }

  int avg = sum / FLAT_SECTION_LENGTH;
  if (avg > MAX_PET_DISTANCE)
  {
    Serial.println("ending due to object being too far");
    return false;
  }
  else if (avg < MIN_PET_DISTANCE)
  {
    Serial.println("ending due to object being too close");
    return false;
  }

  return true;
}

bool Lidar::isIncreasing(int (&array)[READING_LENGTH], int dipTolerance, int overallThreshold, int startIndex, int endIndex)
{
  if ((getAvg(array, endIndex - 2, endIndex) - getAvg(array, startIndex, startIndex + 2)) < overallThreshold)
  {
    Serial.println("not increasing enough"); // remove later
    return false;
  }

  for (int i = startIndex; i < endIndex; ++i)
  {
    if (array[i + 1] - array[i] < -dipTolerance)
    {
      Serial.println("dip outside tolerance");
      return false;
    }
  }

  return true;
}

bool Lidar::isDecreasing(int (&array)[READING_LENGTH], int bumpTolerance, int overallThreshold, int startIndex, int endIndex)
{
  if ((getAvg(array, endIndex - 2, endIndex) - getAvg(array, startIndex, startIndex + 2)) > overallThreshold)
  {
    Serial.println("not decreasing enough"); // remove later
    return false;
  }

  for (int i = startIndex; i < endIndex; ++i)
  {
    if (array[i + 1] - array[i] > bumpTolerance)
    {
      Serial.println("bump outside tolerance"); // remove later
      return false;
    }
  }

  return true;
}

bool Lidar::isPetInFront(int (&readings)[READING_LENGTH])
{
  int filtered[READING_LENGTH] = {};

  // Step 1: Median filter
  medianFilter(readings, filtered);

  // Step 2: Clamp spikes
  clampSpikes(filtered, MAX_SPIKE);

  // Step 3: Remove outliers
  int avg = getAvg(filtered, 0, READING_LENGTH - 1);
  removeOutliers(avg, filtered);

  // REMOVE THIS LATER:
  // for (int i = 0; i < READING_LENGTH; i++)
  // {
  //   Serial.print(i);
  //   Serial.print(": ");
  //   Serial.println(filtered[i]);
  // }

  // Step 4: Apply detection logic
  bool centralFlat = centralFlatSection(filtered);
  // bool decreasingOnLeft = isDecreasing(filtered, BUMP_TOLERANCE, DECREASE_THRESHOLD, 0, READING_LENGTH / 2 - FLAT_SECTION_LENGTH / 2);
  bool increasingOnRight = isIncreasing(filtered, DIP_TOLERANCE, INCREASE_THRESHOLD, READING_LENGTH / 2 - FLAT_SECTION_LENGTH / 2 + 1, 39);

  return centralFlat && increasingOnRight; // && decreasingOnLeft;
}

bool Lidar::isPillarInFront(int (&readings)[READING_LENGTH])
{
  int filtered[READING_LENGTH] = {};

  // Step 1: Median filter
  medianFilter(readings, filtered);

  // Step 2: Clamp spikes
  clampSpikes(filtered, MAX_SPIKE);

  // Step 3: Remove outliers
  int avg = getAvg(filtered, 0, READING_LENGTH - 1);
  removeOutliers(avg, filtered);

  // REMOVE THIS LATER:
  for (int i = 0; i < READING_LENGTH; i++)
  {
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.println(filtered[i]);
  }

  // Step 4: Apply detection logic

  int values[2] = {};

  findMinAndLocation(filtered, values);
  int minIndex = values[0];
  int minValue = values[1];

  if (!(minIndex >= 15 && minIndex <= 30))
  {
    Serial.print("min not in accepted range - ");
    // Serial.println(minIndex);
    return false;
  }

  if (minValue >= MAX_PET_DISTANCE || minValue <= MIN_PET_DISTANCE)
  {
    // Serial.println("pet not in allowable distance range");
    return false;
  }

  bool decreasingOnLeft = isDecreasing(filtered, BUMP_TOLERANCE, DECREASE_THRESHOLD, minIndex - 10, minIndex);
  bool increasingOnRight = isIncreasing(filtered, DIP_TOLERANCE, INCREASE_THRESHOLD, minIndex + 1, minIndex + 10);

  return increasingOnRight && decreasingOnLeft;
}

double Lidar::petSearchStatic() {
  double petDist = 0.0;

  double probe = singleMeasurement();

  if (previousDistance - probe > 100) {
    risingEdgeCount++;

    if (risingEdgeCount == 2) {
      if (probe >= PET_DIST - 100 && 
          probe <= PET_DIST + 100) {
        petDist = probe;
      }
    }
  }
  
  previousDistance = probe;


  return petDist;
}