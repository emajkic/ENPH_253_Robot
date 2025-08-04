#include "States/State2.h"

State2::State2(State* nextState, Claw* claw, PID* pid, Lidar* lidarR, Motor* motorL, Motor* motorR) {
    this->nextState = nextState;
    this->claw = claw;
    this->pid = pid;
    this->lidarR = lidarR;
    this->motorL = motorL;
    this->motorR = motorR;
 }

void State2::execute() {
    pid->usePID();    
}

State* State2::getNextState() {
    double petDistance = lidarR->petSearchRegular();

    if (petDistance != 0) {
        motorL->stop();
        motorR->stop();

        claw->moveClaw(petDistance, Y_SHORT_PET, THETA_RIGHT_PET);

        return this->nextState;
    } else {
        return this;
    }
}