#include "States/State4.h"
#include "States/State5.h"

State4::State4(State* nextState, PID* pid, Sonar* sonar) {
    this->nextState = nextState;
    this->pid = pid;
    this->sonar = sonar;
}

void State4::execute() {
    pid->usePID(BASE_SPEED);
}

State* State4::getNextState() {
    if (sonar->rampDetected()) {
        return this->nextState;
    } else {
        return this;
    }
}