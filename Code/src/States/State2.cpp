#include "States/State2.h"

State2::State2() {
    this->stateStartTime = micros();
 }

void State2::execute() {
    Serial.println("In state 2!");
}

State* State2::getNextState() {
    return this; //for now, stay in state2
}