#ifndef StateManager_h
#define StateManager_h

#include <Arduino.h>

#include "State.h"

class StateManager {
    public:
        StateManager();

        /*
        * Finite state machine progression execution
        */
        void poll(); 
        
    private:
        int currentStateNum;
        State currentState;

        void advanceState();
};

#endif