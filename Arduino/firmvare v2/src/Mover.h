#include <Arduino.h>
#include <Servo.h>

class Mover
{
  private:
    Servo turnServo;
    int straightValue;
    int wheelPower;
    int getNumValue(String a);

  public:
    Mover();
    ~Mover();
    int initServo();
    int execCommand(int commandID, String commandName);
    int turnWheels(int turn);
    int turnWheelsByDegree(int degree);
    int changeStraighValue(String commandName);
    int changeWheelPower(String commandName);
    int startWheelsByValue(int value);
    int startWheelsByTime(String commandName);
    int stopWheels();
    int changeDirection();
    int getStraigthValue();
};
