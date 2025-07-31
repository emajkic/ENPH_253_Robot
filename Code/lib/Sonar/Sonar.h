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

    private:
        int trigPin;
        int echoPin;
};

#endif