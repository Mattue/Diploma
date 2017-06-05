#include "Arduino.h"
//#include <Servo.h>
#include <DipLink.h>
#include <CommandList.h>
#include <Mover.h>
#include <MemoryFree.h>

//int chooser();

DipLink link;

CommandList commandList;

Mover move;
//Servo myServo;

String z;

int chooser(int cmdID, String cmdName)
{
  if (cmdID < 11)
  {
    //команды для DipLink и CommandList
    switch (cmdID)
    {
      case 0:
        break;
      default:
        break;
    }
  }
  else if (cmdID < 31)
  {
    //команды для движков
    switch (cmdID)
    {
      case 20:
      {
        //link.sendMessage("GOT 20");
        int servoValue = move.getStraigthValue();
        link.sendMessage(link.writeMessage( "SERVO_VALUE_" + String(servoValue), "021"));
        return 0;
      }
      default:
        move.execCommand(cmdID, cmdName);
        return 0;
    }
  }
  else if (cmdID < 61)
  {
    //команды для списка
  }

  return 0;
}

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  move.initServo();

  link.enableConnection();
}

String a;
int x;

void loop()
{
  if (Serial.available() > 0)
  {
    a = link.getMessage();
    //link.sendMessage(link.readMessage(a));;
    chooser(link.getCommandID(link.readMessage(a)), link.getCommandMsg(link.readMessage(a)));
  }
}
