#include "States/State7.h"
#include "States/State8.h"

State7::State7(State* nextState, Claw* claw) {
    this->nextState = nextState;
    this->claw = claw;

    timerStart = false;
    moveOn = false;
}

void State7::execute() {
    if (!timerStart) {
        stateStartTime = millis();
        timerStart = true;
    }

    // bool hallFound = claw->sweepForHall();

    if (claw->sweepForHall()) {
        claw->clamp();
        moveOn = true;
    } else if (millis() - stateStartTime > PET_TIMEOUT) {
        moveOn = true;
    }
}

State* State7::getNextState() {
    if (moveOn) {
        claw->windowPosition();
        claw->unclamp(); 
        claw->homeXY();
        claw->homeTheta();

        return this->nextState;
    } else {
        return this;
    }
}