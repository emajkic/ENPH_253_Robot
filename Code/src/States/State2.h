#ifndef State2_h
#define State2_h

#include "State.h"

class State2 : public State {
    public:
        State2(State* nextState, Claw* claw, PID* pid, Lidar* lidarR, Motor* motorL, Motor* motorR);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        PID* pid;
        Lidar* lidarR;
        Motor* motorL;
        Motor* motorR;
        Claw* claw;
};

#endif