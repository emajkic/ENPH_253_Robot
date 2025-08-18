#include "States/State2.h"

State2::State2(State* nextState, PID* pid, Motor* motorL, Motor* motorR) {
    this->nextState = nextState;
    this->pid = pid;
    this->motorL = motorL;
    this->motorR = motorR;

    timerStart = false;
 }

void State2::execute() {
    if (!timerStart) {
        stateStartTime = millis();
        timerStart = true;
    }

    pid->usePID(BASE_SPEED);    
}

State* State2::getNextState() {
    unsigned long now = millis();

    if (now - stateStartTime >= 9000) { // 9 sec
        motorL->stop();
        motorR->stop();
        return this->nextState;
    } else {
        return this;
    }   
}