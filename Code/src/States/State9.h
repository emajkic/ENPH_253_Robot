#ifndef State9_h
#define State9_h

#include "State.h"

class State9 : public State {
    public:
        State9();

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;
};

#endif