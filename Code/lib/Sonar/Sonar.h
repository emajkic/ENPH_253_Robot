#ifndef Sonar_h
#define Sonar_h

#include <Arduino.h>

class Sonar {
    public:
        Sonar(int trigPin, int echoPin);

        /*
        * Get distance sonar reading
        *
        * @return the distance from the sonar to the nearest object [cm]
        */
        int getDistance();

        /*
        * Check if on ramp
        *
        * @return true if ramp detected
        */
        bool rampDetected();

        /*
        * Check if on debris
        *
        * @return true if debris detected
        */
        bool debrisDetected();

    private:
        int trigPin;
        int echoPin;
};

#endif