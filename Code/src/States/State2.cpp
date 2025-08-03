#include "States/State2.h"

State2::State2(State* nextState) {
    this->nextState = nextState;
 }

void State2::execute() {
    
}

State* State2::getNextState() {
    return this; //for now, stay in state2
}