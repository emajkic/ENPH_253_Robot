#include "States/State3.h"
#include "States/State4.h"

State3::State3(State* nextState, Claw* claw) {
    this->nextState = nextState;
    this->claw = claw;

    timerStart = false;
    moveOn = false;
}

void State3::execute() {
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

State* State3::getNextState() {
    if (moveOn) {
        claw->rampPosition();

        return this->nextState;
    } else {
        return this;
    }
}