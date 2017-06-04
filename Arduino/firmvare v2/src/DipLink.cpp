#include "DipLink.h"

int DipLink::getNumLen(int number)
{
  int buf = number;

  int count = (buf == 0) ? 1 : 0;
  while (buf != 0)
  {
      count++;
      buf /= 10;
  }

  return count;
}

String DipLink::zeroAdd(String number)
{
  int count = getNumLen(number.length());

  String msgLenFinal;

  switch (count)
  {
    case 1:
      msgLenFinal = msgLenFinal + "00" + number.length();
      break;
    case 2:
      msgLenFinal = msgLenFinal + '0' + number.length();
      break;
    default:
      break;
  }

  return msgLenFinal;
}

DipLink::DipLink()
{
  connectionEnabled = false;
}

DipLink::~DipLink()
{
  if(connectionEnabled)
  {
    String message = "55013001ENDCONNECTION";
    message += message.length();
    Serial.print(message);
    Serial.end();
  }
}

int DipLink::enableConnection()
{
  if(!connectionEnabled)
  {
    Serial.begin(9600);

    while (true)
    {
      while (Serial.available() <= 0)
      {
        Serial.println(createHeartBeatMessage());
        delay(2000);
      }

      String message = Serial.readString();
      if(readMessage(message).equals("000_BEAT"))
      {
        connectionEnabled = true;
        return 0;// connection enabled
      }
    }
  }

  return 2;//major error
}

int DipLink::checkConnection()
{
  if (connectionEnabled)
  {
    int count;

    while(true)
    {
      count = 0;

      while (Serial.available() <= 0 and count <= 3)
      {
          Serial.print(createHeartBeatMessage());
          count++;
      }

      if(count > 3)
      {
        connectionEnabled = false;
        return 1; //connection break
      }
      else
      {
        String message = Serial.readString();
        if(readMessage(message).equals("000_BEAT"))
        {
          return 0; //connection OK
        }
      }
    }
  }
  else
  {
    connectionEnabled = false;
    return 1; //connection break
  }

  return 2; //major error
}

int DipLink::reconnect()
{
  Serial.end();
  if (enableConnection() != 0)
  {
    return 0;
  }

  return 2; //major error
}

String DipLink::readMessage(String message)
{
  String line = message;
  String resMessage;
  String buf;

  line.trim();

  //get package start info
  for (int i = 0; i < 2; i++)
  {
    buf += line[i];
  }

  if (!buf.equals("55"))
  {
    return "NOT_PACKAGE";
  }

  buf = "";
  line = line.substring(2); //delete package start info

  //get msgLen info
  for (int i = 0; i < 3; i++)
  {
    buf += line[i];
  }

  if (buf[0] == '0')
  {
    if (buf[1] == '0')
    {
      buf.substring(2);
    }
    else
    {
      buf.substring(1);
    }
  }

  int msgLen;
  if ((msgLen = buf.toInt()) == 0)
  {
    return "MSGLEN_ERROR";
  }

  buf = "";
  line = line.substring(3); //delete msgLen info

  //parsing msgID
  for (int i = 0; i < 3; i++)
  {
    buf += line[i];
  }

  resMessage = resMessage + buf + '_';

  buf = "";
  line = line.substring(3); //delete msgID info

  //parsing msg info
  for (int i = 0; i < msgLen; i++)
  {
    buf += line[i];
  }

  resMessage = resMessage + buf;

  buf = "";
  line = line.substring(msgLen); //delete msg info

  //parsing packageLen info
  for (unsigned int i = 0; i < line.length() + 1; i++)
  {
    buf += line[i];
  }

  unsigned int packageLen;
  if ((packageLen = buf.toInt()) == 0)
  {
    return "PACKAGELEN_ERROR";
  }

  //chek for package integrity
  if (packageLen != message.length())
  {
    return "PACKAGE_BROKEN";
  }

  return resMessage;
}

String DipLink::writeMessage(String message, String msgID)
{
  String package = "55";

  String msgLen = zeroAdd(message);

  package = package + msgLen + msgID + message;
  package += (package.length() + getNumLen(package.length()));
  package.toUpperCase();

  return package;
}

String DipLink::createHeartBeatMessage()
{
  return writeMessage("BEAT", "000");
}

int DipLink::sendMessage(String message)
{
  if(connectionEnabled)
  {
    Serial.println(message);
    return 0;
  }
  return 1;//no connection
}

String DipLink::getMessage()
{
  if (connectionEnabled)
  {
    String message = Serial.readString();
    Serial.println(message);
    return message;
  }
  return "";
}

int DipLink::getCommandID(String command)
{
  String commandID;
  int i = 0;

  while ((command[i] == 0) and i < 3)
  {
    i++;
  }

  while(command[i] != '_')
  {
    commandID += command[i];
    i++;
  }

  if(commandID.toInt() != 0)
  {
    return commandID.toInt();
  }
  else
  {
    return 1;//not numberic value
  }
}

String getCommandMsg(String command)
{
  String commandName;

  for(unsigned int i = 4; i < command.length(); i++)
  {
    commandName += command[i];
  }

  return commandName;
}
