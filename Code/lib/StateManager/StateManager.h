#ifndef StateManager_h
#define StateManager_h

#include <Arduino.h>

class StateManager {
    public:
        StateManager();

        /*
        * Finite state machine progression execution
        */
        void poll(); 
        
    private:
        void advanceState();
};

#endif