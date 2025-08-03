#include "States/State2.h"

State2::State2(State* nextState, PID* pid, Lidar* lidarR) {
    this->nextState = nextState;
    this->pid = pid;
    this->lidarR = lidarR;
 }

void State2::execute() {
    pid->usePID();    
}

State* State2::getNextState() {
    double petDistance = lidarR->petSearchRegular();

    if (petDistance != 0) {
        return this->nextState;
    } else {
        return this;
    }
}