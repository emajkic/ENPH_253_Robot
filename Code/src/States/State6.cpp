#include "States/State6.h"
#include "States/State7.h"

State6::State6(State* nextState, PID* pid, Lidar* lidarL, Claw* claw, Motor* motorL, Motor* motorR) {
    this->nextState = nextState;
    this->pid = pid;
    this->lidarL = lidarL;
    this->claw = claw;
    this->motorL = motorL;
    this->motorR = motorR;
}

void State6::execute() {
    pid->usePID(BASE_SPEED);
}

State* State6::getNextState() {
    double petDistance = lidarL->petSearchRegular();

    if (petDistance != 0) {
        motorL->stop();
        motorR->stop();

        claw->moveClaw(petDistance, Y_SHORT_PET, THETA_LEFT_PET);

        return this->nextState;
    } else {
        return this;
    }
}