#include "States/State4.h"
#include "States/State5.h"

State4::State4(State* nextState, PID* pid) {
    this->nextState = nextState;
    this->pid = pid;
}

void State4::execute() {
    pid->usePID(BASE_SPEED);
}

State* State4::getNextState() {
    return this;
}