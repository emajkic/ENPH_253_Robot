#ifndef PID_h
#define PID_h

#include <Arduino.h>
#include "Motor.h"

class PID {
    public:
        /*
        * Class Constructor
        */
        PID(Motor &leftMotor, Motor &rightMotor); //add more param once figured out

        /*
        * Use PID control loop
        */
        void usePID();

        /*
        * Set PID error to 0
        */
        void resetPID();

        /*
        * Setters and Getters
        */
        void setKP(int KP) { this->KP = KP; }
        void setKI(int KI) { this->KI = KI; };
        void setKD(int KD) { this->KD = KD; };

        int getKP() { return this->KP; }
        int getKI() { return this->KI; }
        int getKD() { return this->KD; }
        int getError() { return this->error; }

        //ADD WAY MORE AS NEEDED, + THINGS RELATED TO SPEED
        void consts(); // FOR TESTING -----------------------

    private:
        int KP;
        int KD;
        int KI;

        long lastTime;

        int error;
        int lastError;

        Motor &leftMotor;
        Motor &rightMotor;

        void doPIDLine();
        int getErrorLine(); 
};

#endif