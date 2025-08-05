#include "States/State8.h"
#include "States/State9.h"

State8::State8(State* nextState, PID* pid, Lidar* lidarL, Motor* motorL, Motor* motorR, Claw* claw) {
    this->nextState = nextState;
    this->pid = pid;
    this->lidarL = lidarL;
    this->motorL = motorL;
    this->motorR = motorR;
    this->claw = claw;
}

void State8::execute() {
    pid->usePID(BASE_SPEED);
}

State* State8::getNextState() {
    double petDistance = lidarL->petSearchRegular();

    if (petDistance != 0) {
        motorL->stop();
        motorR->stop();

        claw->moveClaw(petDistance, Y_TALL_PET, THETA_LEFT_PET);

        return this->nextState;
    } else {
        return this;
    }
}