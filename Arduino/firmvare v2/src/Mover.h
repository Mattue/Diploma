#include <Arduino.h>
#include <Servo.h>

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
    int startWheels();
};
