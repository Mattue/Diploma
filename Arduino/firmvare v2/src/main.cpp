#include "Arduino.h"
#include <Servo.h>
#include <DipLink.h>
#include <CommandList.h>

DipLink link;

CommandList commandList;

void setup()
{
  Serial.begin(9600);
}

String a;
int b = 0;

void loop()
{
  while(Serial.available() > 0)
  {
    a = Serial.readString();
    //list check
    /*b = a.toInt();
    switch (b)
    {
      case 1:
        Serial.print(commandList.getSize());
        break;
      case 2:
        Serial.print(commandList.addLast("555_NONO"));
        break;
      case 3:
        Serial.print(commandList.removeLast());
        break;
      case 4:
        Serial.print(commandList.getCommandID());
        break;
      default:
        break;
    }*/
  }
}
