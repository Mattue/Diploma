#include "Mover.h"

#define IN3 5
#define IN4 4
#define ENB 3
#define SERVOPIN 9
#define TURN 20
#define LEFT -1
#define STRAIGHT 0
#define RIGHT 1

Mover::Mover()
{
  straightValue = 90;
  wheelPower = 130;

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 0);

  TurnServo.attach(SERVOPIN);
  TurnServo.write(straightValue);
}

Mover::~Mover()
{
  digitalWrite(ENB, 0);
}

int Mover::execCommand(int commandID, String commandName)
{
  switch(commandID)
  {
    case 111:
      return turnWheels(STRAIGHT);
    case 112:
      return turnWheels(LEFT);
    case 113:
      return turnWheels(RIGHT);
    case 114:
      return changeStraighValue(commandName);
    default:
      return 1;
  }
}

int Mover::getNumValue(String commandName)
{
  String commandValue;
  int i = commandName.length();

  while (commandValue[i] != '_')
  {
    commandValue += commandName[i];
    i--;
  }

  if(commandValue.length() <= 1)
  return commandValue.toInt();

  String revValue;

  for(int i = commandValue.length(); i != 0; i--)
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
      TurnServo.write(straightValue - TURN);
      return 0;
    case 0:
      TurnServo.write(straightValue);
      return 0;
    case 1:
      TurnServo.write(straightValue + TURN);
      return 0;
    default:
      return 1;
  }
}

int Mover::turnWheelsByDegree(int degree)
{
  TurnServo.write(straightValue + degree);
  return 0;
}

int Mover::changeStraighValue(String commandName)
{
    straightValue = getNumValue(commandName);
    return 0;
}

int Mover::changeWheelPower(String commandName)
{
  wheelPower = getNumValue(commandName);
  return 0;
}

int Mover::startWheelsByValue(int value)
{
  if (value < 0)
  {
    digitalWrite(ENB, wheelPower);
    return 0;
  }
}

int Mover::startWheelsByTime(int value)
{
  long time;
  time = millis();
  digitalWrite(ENB, wheelPower);

  if (value > 2)
  {

  }

  while (value <= time)
  {
    time = millis();
  }

  digitalWrite(ENB, 0);

  return 0;
}

int stopWheels()
{
  digitalWrite(ENB, 0);
  return 0;
}
