#ifndef PostDebris_h
#define PostDebris_h

#include "State.h"
#include "Constants.h"

class PostDebris : public State {
    public:
        PostDebris(State* nextState, Sonar* sonar, PID* pid, Motor* leftMotor, Motor* rightMotor);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        Sonar* sonar; 
        PID* pid; 
        Motor* leftMotor; 
        Motor* rightMotor; 
};

#endif