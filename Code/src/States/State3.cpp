#include "States/State3.h"
#include "States/State4.h"

State3::State3(State* nextState) {
    this->nextState = nextState;
}

void State3::execute() {
}

State* State3::getNextState() {
}