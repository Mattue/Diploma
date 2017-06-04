#include <Arduino.h>
#include <Servo.h>
#include <DipLink.h>

class Mover
{
  private:
    Mover();
    ~Mover();
    Servo TurnServo;
    int straightValue;
    int wheelPower;
    int execCommand(int commandID, String commandName);
    int getNumValue(String a);

  public:
    int turnWheels(int turn);
    int turnWheelsByDegree(int degree);
    int changeStraighValue(String commandName);
    int changeWheelPower(String commandName);
    int startWheelsByValue(int value);
    int startWheelsByTime(String commandName);
    int stopWheels();
    int changeDirection();
};
