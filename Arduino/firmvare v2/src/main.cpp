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
bool memoryAvailable = true;

int chooser(int cmdID, String cmdName);

int listExec ()
{
  while(commandList.getSize() != 0)
  {
    if (chooser(commandList.getCommandID(), commandList.getCommandName()) == 0)
    {
      commandList.removeFirst();
      link.sendMessage(link.writeMessage("STATUS_0", "002"));
    }

    if (Serial.available() > 0)
    {
      String a = link.getMessage();
      if (chooser(link.getCommandID(link.readMessage(a)), link.getCommandMsg(link.readMessage(a))) == 0)
      {
        return 1;
      }
    }
  }

  delay(1000);

  link.sendMessage(link.writeMessage("STOP_EXEC_COMAND_LIST", "008"));

  return 0;
}

int chooser(int cmdID, String cmdName)
{
  if (cmdID < 11)
  {
    //команды для DipLink и CommandList
    switch (cmdID)
    {
      case 0:
        break;
      case 7:
      {
        listExec();
        //move.execCommand(commandList.getCommandID(), commandList.getCommandName());
        break;
      }
      case 8:
      {
        move.execCommand(19, "STOP_WHEELS");
        move.execCommand(11, "TURN_STRAIGHT");
        commandList.clearList();
        return 0;
        break;
      }
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
      case 14:
      {
        move.changeStraighValue(cmdName);
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
    switch(cmdID)
    {
      case 31:
      {
        if (memoryAvailable == true)
        {
          if (link.getCommandID(cmdName) == 23)
          {
            commandList.wait(cmdName);
          }
          else
          {
            commandList.addLast(cmdName);
          }
          if (freeMemory() <= 500)
          {
            memoryAvailable = false;
            link.sendMessage(link.writeMessage( "NO_MEMORY", "004"));
          }
        }
        else
        {
          link.sendMessage(link.writeMessage( "NO_MEMORY", "004"));
        }
        break;
      }
      case 32:
      {
        commandList.removeLast();
        if (freeMemory() > 700)
        {
          memoryAvailable = true;
        }
        break;
      }
      case 33:
      {
        commandList.clearList();
        memoryAvailable = true;
        break;
      }
      case 34:
      {
        link.sendMessage(link.writeMessage("SIZE_" + String(commandList.getSize()), "034"));
        break;
      }
      case 35:
      {
        commandList.wait(cmdName);
      }
      default:
        break;
    }
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
    delay(1000);
    //Serial.println(a);
    //link.sendMessage(link.readMessage(a));;
    chooser(link.getCommandID(link.readMessage(a)), link.getCommandMsg(link.readMessage(a)));
  }
}
