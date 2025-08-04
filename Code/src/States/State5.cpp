#include "States/State5.h"
#include "States/State6.h"

State5::State5(State* nextState, PID* pid, Claw* claw, Sonar* sonar) {
    this->nextState = nextState;
    this->pid = pid;
    this->claw = claw;
    this->sonar = sonar;

    timerStart = false;
}

void State5::execute() {
    if (!timerStart) {
        stateStartTime = millis();
        timerStart = true;
    }

    pid->usePID(RAMP_SPEED);

    if (millis() - stateStartTime >= RAMP_DROPOFF_TIME) {
        claw->unclamp();
    }
}

State* State5::getNextState() {
    if (sonar->endRampDetected()) {
        return this->nextState;
    } else {
        return this;
    }
}