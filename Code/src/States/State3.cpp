#include "States/State3.h"
#include "States/State4.h"

State3::State3(State* nextState, Claw* claw, Lidar* lidarR) {
    this->nextState = nextState;
    this->claw = claw;
    this->lidarR = lidarR;
}

bool moveOn = false;

void State3::execute() {
    bool hallFound = claw->sweepForHall();

    if (hallFound) {
        claw->clamp();
    } else {

    }

    // claw->moveClaw(dist, );
}

State* State3::getNextState() {

}