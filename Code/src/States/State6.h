#ifndef State6_h
#define State6_h

#include "State.h"

class State6 : public State {
    public:
        State6(State* nextState, PID* pid, Lidar* lidarL, Claw* claw, Motor* motorL, Motor* motorR);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        PID* pid;
        Lidar* lidarL;
        Claw* claw;
        Motor* motorL;
        Motor* motorR;
};

#endif