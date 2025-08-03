#include "Sonar.h"
#include "Constants.h"

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

/*
* Get distance sonar reading
*
* @return the distance from the sonar to the nearest object [cm]
*/
int Sonar::getDistance() {
    long duration;
    int distanceCm;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distanceCm = duration * 0.034 / 2;

    return distanceCm;
}

/*
* Check if on ramp
*
* @return true if ramp detected
*/
bool Sonar::rampDetected() {
    int dist = getDistance();

    if (dist == (SONAR_BASE_DIST + SONAR_RAMP_INCREASE)) {
        return true;
    } else {
        return false;
    }
}

/*
* Check if on debris
*
* @return true if debris detected
*/
bool Sonar::debrisDetected() {
    int dist = getDistance();

    if (dist == (SONAR_BASE_DIST + SONAR_DEBRIS_INCREASE)) {
        return true;
    } else {
        return false;
    }
}