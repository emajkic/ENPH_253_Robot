#ifndef State1_h
#define State1_h

#include "State.h"

class State1 : public State {
    public:
        State1(State* nextState, int payload);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;
        int mypayload;
};

#endif