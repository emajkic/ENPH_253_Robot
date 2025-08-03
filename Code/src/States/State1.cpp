#include "States/State1.h"
#include "States/State2.h"

State1::State1(State* nextState) : nextState(nextState) {
 }

void State1::execute() {
    Serial.print("In state 1: ");
}

State* State1::getNextState() {

    // if (ct - stateStartTime < 4000) { //4 secs
    //     Serial.println("State 1 ret itself");
    //     return this;
    // } else {
    //     Serial.println("State 1 ret next state");
    //     return this->nextState;
    // }
}