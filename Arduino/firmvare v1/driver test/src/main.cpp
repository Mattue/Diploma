#include "Arduino.h"
#include <Servo.h>

int IN3 = 5;
int IN4 = 4;
int ENB = 3;
int TurnPIN = 9;

Servo myservo;

void setup()
{
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 0);

  myservo.attach(TurnPIN);
  myservo.write(90);

  Serial.begin(57600);
}

void onHandler()
{
  analogWrite(ENB, 150);
}

void offHandler()
{
  analogWrite(ENB, 0);
}

void turnHandler(int turn)
{
  if(turn == -1)
  {
    myservo.write(70);
  }
  else if (turn == 1)
  {
    myservo.write(110);
  }
  else if (turn == 0)
  {
  	myserov.write(90);
  }
}

String a;

void loop()
{

  while(Serial.available() > 0)
  {
    //Serial.write(Serial.read());

    a = Serial.readString();

    if (a == "on")
    {
      onHandler();
      Serial.write("Switching on!");
    }
    if (a == "off")
    {
      offHandler();
      Serial.write("Switching off!");
    }
    if (a == "left")
    {
      turnHandler(-1);
      Serial.write("Left tutn!");
    }
    if (a == "right")
    {
      turnHandler(1);
      Serial.write("Rigth turn!");
    }
    if (a == "straight")
    {
      turnHandler(0);
      Serial.write("90 gedrees!");
    }
  }

  /*digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENB, 55);
  delay(2000);
  analogWrite(ENB, 105);
  delay(2000);
  analogWrite(ENB, 255);
  delay(2000);

  analogWrite(ENB, 0);
  delay(5000);*/
}
