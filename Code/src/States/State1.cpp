#include "States/State1.h"
#include "States/State2.h"

State1::State1(State* nextState) {
    this->nextState = nextState;
}

void State1::execute() {
}

State* State1::getNextState() {
    if (digitalRead(ON_PIN) == LOW) {
        return this;
    } else if (digitalRead(ON_PIN) == HIGH) {
        return this->nextState;
    }
}