#include "CommandList.h"

int CommandList::parseCommandID(String command)
{
  String commandID;
  int i = 0;

  //removing all 0 from begin
  while ((command[i] == 0) and i < 3)
  {
    i++;
  }

  while (command[i] != '_')
  {
    commandID += command[i];
    i++;
  }

  return commandID.toInt();
}

String CommandList::parseCommandName(String command)
{
  String commandName;

  for(unsigned int i = 4; i < command.length(); i++)
  {
    commandName += command[i];
  }

  return commandName;
}

void CommandList::createList(String command)
{
  head = new listElem;
  tail = new listElem;
  head->commandID = parseCommandID(command);
  head->commandName = parseCommandName(command);
  head->next = 0;
  head->prev = 0;
  tail = head;
  size++;
}

int CommandList::getNumValue(String commandName)
{
  String commandValue;
  int i = commandName.length();

  while (commandName[i] != '_')
  {
    commandValue += commandName[i];
    i--;
  }

  commandValue.trim();

  if(commandValue.length() <= 1)
  return commandValue.toInt();

  String revValue;

  for(int i = commandValue.length() - 1; i >= 0; i--)
  {
    revValue += commandValue[i];
  }
  return revValue.toInt();
}

CommandList::CommandList()
{
    size = 0;
    head = 0;
    tail = 0;
}

CommandList::~CommandList()
{
  while (size != 0)
  {
    removeLast();
  }

  delete tail;
  delete head;
}

int CommandList::addFirst(String command)
{
  if (size == 0)
  {
    createList(command);
    return 0;
  }

  listElem* add = new listElem;
  add->commandID = parseCommandID(command);
  add->commandName = parseCommandName(command);
  add->prev = 0;
  add->next = head;
  head->prev = add;
  head = add;
  size++;

  add = 0;

  return 0;
}

int CommandList::addLast(String command)
{

    if (size == 0)
    {
      createList(command);
      return 0;
    }

    listElem* add = new listElem;;
    add->commandID = parseCommandID(command);
    add->commandName = parseCommandName(command);
    add->prev = tail;
    add->next = 0;
    tail->next = add;
    tail = add;
    size++;

    add = 0;

    return 0;
}

int CommandList::removeFirst()
{
  if (size != 0)
  {
    if (size == 1)
    {
      head = 0;
      tail = 0;
      size--;
    }
    else
    {
      head = head->next;
      delete head->prev;
      size--;
    }
    return 0;
  }
  return 0;
}

/*int CommandList::removeLast()
{
  if (size != 0)
  {
    if (size == 1)
    {
      head = 0;
      tail = 0;
      size--;
    }
    else
    {
      tail = tail->prev;
      delete tail->next;
      size--;
    }
    return 0;
  }
  return 0;
}*/

int CommandList::removeLast()
{
  if (size != 0)
  {
    if (tail->commandID == 23)
    {
      while (tail->commandID == 23)
      {
        if (size == 1)
        {
          head = 0;
          tail = 0;
          size--;
        }
        else
        {
          tail = tail->prev;
          delete tail->next;
          size--;
        }
      }
    }
    else
    {
      if (size == 1)
      {
        head = 0;
        tail = 0;
        size--;
      }
      else
      {
        tail = tail->prev;
        delete tail->next;
        size--;
      }
    }
  }

  return 0;
}

int CommandList::getCommandID()
{
  if (size != 0)
  {
    return head->commandID;
  }
  return 0;
}

String CommandList::getCommandName()
{
  if (size != 0)
  {
    return head->commandName;
  }
  return "";
}

int CommandList::getSize()
{
  return size;
}

int CommandList::clearList()
{
  while (size != 0)
  {
    removeLast();
  }
  return 0;
}

int CommandList::wait(String command)
{
  int timeToMove = getNumValue(command);

  int countOf2 = 0;
  bool countOf1 = false;

  if (timeToMove%2 == 0)
  {
    countOf2 = timeToMove/2;
  }
  else
  {
    timeToMove--;
    countOf1 = true;
    countOf2 = timeToMove / 2;
  }

  for (int i = 0; i < countOf2; i++)
  {
    addLast("023_WAIT_2");
  }

  if (countOf1)
  {
    addLast("023_WAIT_1");
  }

  return 0;
}
