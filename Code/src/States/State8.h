#ifndef State8_h
#define State8_h

#include "State.h"

class State8 : public State {
    public:
        State8(State* nextState, PID* pid, Lidar* lidarL, Motor* motorL, Motor* motorR, Claw* claw);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        PID* pid;
        Lidar* lidarL;
        Motor* motorL;
        Motor* motorR;
        Claw* claw;
};

#endif