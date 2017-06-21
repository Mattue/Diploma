#include "Mover.h"

#define IN3 5
#define IN4 4
#define ENB 3
#define SERVOPIN 9
#define TURN 20
#define INF -1
#define LEFT -1
#define STRAIGHT 0
#define RIGHT 1

bool direction = true;

Mover::Mover()
{
  straightValue = 90;
  wheelPower = 50;

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(IN3, !direction);
  digitalWrite(IN4, direction);
  analogWrite(ENB, 0);

  //turnServo.attach(turnPin, 70, 110);
  //turnServo.write(straightValue);
}

Mover::~Mover()
{
  digitalWrite(ENB, 0);
}

int Mover::initServo()
{
  turnServo.attach(SERVOPIN);
  turnServo.write(straightValue);

  return 0;
}

int Mover::execCommand(int commandID, String commandName)
{
  switch(commandID)
  {
    case 11:
      return turnWheels(STRAIGHT);
    case 12:
      return turnWheels(LEFT);
    case 13:
      return turnWheels(RIGHT);
    case 14:
      return changeStraighValue(commandName);
    case 15:
      return changeWheelPower(commandName);
    case 16:
      return startWheelsByValue(INF);
    case 17:
      return startWheelsByValueBkwd(INF);
    case 18:
      return startWheelsByTime(commandName);
    case 19:
      return stopWheels();
    case 20:
      return getStraigthValue();
    case 23:
      return wait(commandName);
    default:
      return 1;
  }
}

int Mover::getNumValue(String commandName)
{
  String commandValue;
  int i = commandName.length();

  while (commandName[i] != '_')
  {
    commandValue += commandName[i];
    i--;
  }

  commandValue.trim();

  if(commandValue.length() <= 1)
  return commandValue.toInt();

  String revValue;

  for(int i = commandValue.length() - 1; i >= 0; i--)
  {
    revValue += commandValue[i];
  }
  return revValue.toInt();
}

int Mover::turnWheels(int turn)
{
  switch (turn)
  {
    case -1:
      turnServo.write(straightValue - TURN);
      return 0;
    case 0:
      turnServo.write(straightValue);
      return 0;
    case 1:
      turnServo.write(straightValue + TURN);
      return 0;
    default:
      return 1;
  }
}

int Mover::turnWheelsByDegree(int degree)
{
  turnServo.write(straightValue + degree);
  return 0;
}

int Mover::changeStraighValue(String commandName)
{
    straightValue = getNumValue(commandName);

    if (straightValue < 70)
    straightValue = 70;

    if (straightValue > 110)
    straightValue = 110;

    turnWheels(0);
    return 0;
}

int Mover::changeWheelPower(String commandName)
{
  wheelPower = getNumValue(commandName);
  return 0;
}

int Mover::startWheelsByValue(int value)
{
  stopWheels();

  if (direction == false)
  changeDirection();

  if (value < 0)
  {
    analogWrite(ENB, wheelPower);
    return 0;
  }
}

int Mover::startWheelsByValueBkwd(int value)
{
  stopWheels();

  if (direction == true)
  changeDirection();

  if (value < 0)
  {
    analogWrite(ENB, wheelPower);
    return 0;
  }
}

int Mover::startWheelsByTime(String commandName)
{
  int timeToMove = getNumValue(commandName)*1000;

  startWheelsByValue(INF);
  delay(timeToMove);
  stopWheels();

  return 0;
}

int Mover::stopWheels()
{
  analogWrite(ENB, 0);
  return 0;
}

int Mover::changeDirection()
{
  direction = !direction;
  digitalWrite(IN3, !direction);
  digitalWrite(IN4, direction);

  return 0;
}

int Mover::getStraigthValue()
{
  return straightValue;
}

int Mover::wait(String commandName)
{
  int timeToMove = getNumValue(commandName)*1000;

  delay(timeToMove);

  return 0;
}
