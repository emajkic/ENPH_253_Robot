#include "States/State3.h"
#include "States/State4.h"

State3::State3(State* nextState, Claw* claw, Lidar* lidarR) {
    this->nextState = nextState;
    this->claw = claw;
    this->lidarR = lidarR;
}

void State3::execute() {
    double dist = lidarR->petSearchRegular();

    // claw->moveClaw(dist, );
}

State* State3::getNextState() {
}