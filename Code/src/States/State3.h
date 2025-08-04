#ifndef State3_h
#define State3_h

#include "State.h"

class State3 : public State {
    public:
        State3(State* nextState, Claw* claw, Lidar* lidarR);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        Claw* claw;
        Lidar* lidarR;
};

#endif