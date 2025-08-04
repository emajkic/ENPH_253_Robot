#include "States/PostDebris.h"
// put next state here: #include

bool moveToNext = false;

PostDebris::PostDebris(State *nextState, Sonar *sonar, PID *pid, Motor *leftMotor, Motor *rightMotor)
{
    this->nextState = nextState;

    this->sonar = sonar;
    this->pid = pid;
}

void PostDebris::execute()
{
    // this will be triggered when we exit the debris

    /*
    while the readings from the QRDs both do not have the line
    turn both motors at the same speed (slow) so it turns left for a set amt of time (left motor forwards, right back)
    do the same to turn right
    wherever it sees the line, immediately stop the chassis
    do pid
    */

    unsigned long startTime = millis();

    while (digitalRead(QRD_PIN_LEFT) && digitalRead(QRD_PIN_RIGHT))
    {
        if (millis() - startTime > LEFT_TURNING_TIME_DEBRIS) // all in milliseconds
        {
            leftMotor->setSpeed(MIN_SPEED, Direction::FORWARD);
            rightMotor->setSpeed(MIN_SPEED, Direction::BACKWARD);
        }
        else
        {
            leftMotor->setSpeed(MIN_SPEED, Direction::BACKWARD);
            rightMotor->setSpeed(MIN_SPEED, Direction::FORWARD);
        }
    }

    pid->usePID(); // once found, resume PID (should this be in the next state?)

    moveToNext = true;
}

State *PostDebris::getNextState()
{
    if (!moveToNext)
    {
        return this;
    }
    else
    {
        return this->nextState;
    }
}