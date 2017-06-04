#include "Arduino.h"
#include <Servo.h>
#include <DipLink.h>
#include <CommandList.h>

DipLink link;

CommandList commandList;

String z;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  //Serial.begin(9600);
  if(link.enableConnection() != 0)
  {
    digitalWrite(13, HIGH);
  }
}

String a;
int x;

void loop()
{
  while(Serial.available() > 0)
  {
    //diplink check
    Serial.println("wait for it");
    z = Serial.readString();
    z = link.readMessage(z);
    x = link.getCommandID(z);
    Serial.println(x);

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
