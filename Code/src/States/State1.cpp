#include "States/State1.h"
#include "States/State2.h"

State1::State1(State* nextState) : nextState(nextState) {
    this->stateStartTime = millis();
 }

void State1::execute() {
    Serial.print("In state 1: ");
}

State* State1::getNextState() {
    unsigned long ct = millis();
    Serial.print("Current time in state 1: ");
    Serial.println(ct-stateStartTime);

    if (ct - stateStartTime < 4000) { //4 secs
        Serial.println("State 1 ret itself");
        return this;
    } else {
        Serial.println("State 1 ret next state");
        return this->nextState;
    }
}