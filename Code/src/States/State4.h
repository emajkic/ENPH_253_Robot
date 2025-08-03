#ifndef State4_h
#define State4_h

#include "State.h"

class State4 : public State {
    public:
        State4();

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;
};

#endif