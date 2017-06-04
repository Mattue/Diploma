#include "Arduino.h"
//#include <Servo.h>
#include <DipLink.h>
#include <CommandList.h>
#include <Mover.h>

DipLink link;

CommandList commandList;

Mover move;
//Servo myServo;

String z;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  move.initServo();

  //myServo.attach(9);
  //myServo.write(90);

  //Serial.begin(9600);
  //if(link.enableConnection() != 0)
  //{
  //  digitalWrite(13, HIGH);
  //}

  //move.execCommand(12, "TURN_LEFT");
  //delay(2000);
  //move.execCommand(13, "TURN_RIGHT");
  //delay(2000);
  //move.execCommand(11, "STRAIGHT");
  //delay(2000);
  //move.execCommand(14, "NEW_STRAIGHT_80");
  //delay(2000);
  //move.execCommand(12, "STRAIGHT");
  //delay(2000);
  //move.execCommand(16, "MOVE");
  //delay(2000);
  //move.execCommand(18, "STOP");
  //delay(2000);
  //move.execCommand(15, "NEW_POWER_255");
  //delay(2000);
  //move.execCommand(16, "MOVE");
  //delay(2000);
  //move.execCommand(18, "STOP");
  //delay(2000);
  //move.execCommand(17, "MOVE_SEC_2");
  //delay(5000);
  //move.execCommand(19, "CHANGE_DIR");
  //delay(2000);
  //move.execCommand(16, "MOVE");
  //delay(2000);
  //move.execCommand(18, "STOP");
  //delay(2000);

  //move.deleteMe();
}

String a;
int x;

void loop()
{
  while(Serial.available() > 0)
  {
    a = Serial.readString();

    //diplink check
    Serial.println("wait for it");
    link.sendMessage(link.writeMessage("BOOM", "003"));
    //Serial.println(x);

    //a = Serial.readString();
    //message create/parse check
    //String c = link.createHeartBeatMessage();
    //Serial.print(c);

    //list check
    /*int b = a.toInt();
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
