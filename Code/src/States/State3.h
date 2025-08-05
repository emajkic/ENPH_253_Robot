#ifndef State3_h
#define State3_h

#include "State.h"

class State3 : public State {
    public:
        State3(State* nextState, Claw* claw);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        bool moveOn;
        bool timerStart;

        Claw* claw;
};

#endif