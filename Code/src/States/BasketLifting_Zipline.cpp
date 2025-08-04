#include "States/BasketLifting_Zipline.h"
// put next state here: #include

bool moveToNextZip = false;

BasketLifting_Zipline::BasketLifting_Zipline(State* nextState, Motor* leftMotor, Motor* rightMotor)
{
    this->nextState = nextState;

    this->leftMotor = leftMotor; 
    this->rightMotor = rightMotor; 
}

void BasketLifting_Zipline::execute()
{
// this will be triggered when we have placed pet 7 in the basket 

  // 1. Lift basket 
  // danny has the code written for this -> get him to send it 

  // 2. move back until basket switches connected to platform read LO (do these exist yet?), then stop

  while (digitalRead(BASKET_SWITCH_PIN)) { // bc basket lifting onto zipline means the switch will be release and we'll have that be LO
    leftMotor->setSpeed(MIN_SPEED, Direction::BACKWARD); 
    rightMotor->setSpeed(MIN_SPEED, Direction::BACKWARD); 

  }

  leftMotor->stop(); 
  rightMotor->stop(); 
   

    moveToNextZip = true;
}

State *BasketLifting_Zipline::getNextState()
{
    if (!moveToNextZip)
    {
        return this;
    }
    else
    {
        return this->nextState;
    }
}