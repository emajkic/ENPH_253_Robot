#ifndef State7_h
#define State7_h

#include "State.h"

class State7 : public State {
    public:
        State7();

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;
};

#endif