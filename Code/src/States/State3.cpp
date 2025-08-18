#include "States/State3.h"
#include "States/State4.h"

State3::State3(State* nextState, Claw* claw) {
    this->nextState = nextState;
    this->claw = claw;

    moveOn = false;
}

void State3::execute() {
    claw->moveClaw(30, 10, 24);

    delay(500);

    claw->clamp();

    delay(2000);

    moveOn = true;
}

State* State3::getNextState() {
    if (moveOn) {
        claw->homeXY();

        return this->nextState;
    } else {
        return this;
    }
}