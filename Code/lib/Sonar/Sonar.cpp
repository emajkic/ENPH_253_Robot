#include "Sonar.h"

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