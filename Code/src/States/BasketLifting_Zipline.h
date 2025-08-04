#ifndef BasketLifting_Zipline_h
#define BasketLifting_Zipline_h

#include "State.h"
#include "Constants.h"

class BasketLifting_Zipline : public State {
    public:
        BasketLifting_Zipline(State* nextState, Motor* leftMotor, Motor* rightMotor);

        void execute() override;

        State* getNextState() override;

    private:
        State* nextState;    
        unsigned long stateStartTime;

        Motor* leftMotor; 
        Motor* rightMotor; 
};

#endif