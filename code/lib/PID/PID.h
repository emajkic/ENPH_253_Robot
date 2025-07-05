#ifndef PID_h
#define PID_h

#include <Arduino.h>
#include <cmath>
#include "Motor.h"

enum class PIDType {
    LineFollower,
    CompassFollower
};

class PID {
    public:
        /*
        * Class Constructor
        */
        PID(PIDType pidType, Motor &leftMotor, Motor &rightMotor); //add more param once figured out

        /*
        * Use PID control loop
        */
        void usePID();

        /*
        * Set PID error to 0
        */
        void resetPID();

        /*
        * Check if both sensors on white
        *
        * @return true if both sensors are on white
        */
        bool bothOnWhite();

        /*
        * Setters and Getters
        */
        void setKP(int KP) { this->KP = KP; }
        void setKI(int KI) { this->KI = KI; };
        void setKD(int KD) { this->KD = KD; };

        int getKP() { return this->KP; }
        int getKI() { return this->KI; }
        int getKD() { return this->KD; }

        int getErrorLine(); 

       //ADD WAY MORE AS NEEDED, + THINGS RELATED TO SPEED

    private:
        PIDType pidType;
        int KP;
        int KD;
        int KI;

        long lastTime;
        long timeOfLastChange;

        volatile int error;
        volatile int lastError;
        volatile int lastDifferentError;

        Motor &leftMotor;
        Motor &rightMotor;

        void doPIDLine();
        void doPIDCompass();

        //int getErrorLine(); MOVED UP FOR TEST
        int getErrorCompass();
};

#endif