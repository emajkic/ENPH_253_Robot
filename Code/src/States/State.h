#ifndef State_h
#define State_h

#include <Arduino.h>
#include <iostream>

// State interface (Abstract Class -> Concrete implementations for each enumerated state)
class State {
    public: 
        /*
        * Execute this state
        */
        virtual void execute() = 0;

        /*
        * Obtain next state
        * @return next State in FSM progression
        */
        virtual State* getNextState() = 0;        
};

#endif