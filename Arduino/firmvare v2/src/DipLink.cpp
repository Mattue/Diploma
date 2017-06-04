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
}

DipLink::~DipLink()
{
}

String DipLink::readMessage(String input)
{
  String line = input;
  String message;
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

  message = message + buf + '_';

  buf = "";
  line = line.substring(3); //delete msgID info

  //parsing msg info
  for (int i = 0; i < msgLen; i++)
  {
    buf += line[i];
  }

  message = message + buf;

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
  if (packageLen != input.length())
  {
    return "PACKAGE_BROKEN";
  }

  return message;
}

String DipLink::writeMessage(String input, String msgID)
{
  String package = "55";

  String msgLen = zeroAdd(input);

  package = package + msgLen + msgID + input;
  package += (package.length() + getNumLen(package.length()));
  package.toUpperCase();

  return package;
}

String DipLink::createHeartBeatMessage()
{
  String package = "55004000BEAT";

  package += package.length();

  return package;
}
