#ifndef State8_h
#define State8_h

#include "State.h"

class State8 : public State {
    public:
        State8();

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;
};

#endif