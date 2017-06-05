#include "ExecuteClass.h"

ExecuteClass::ExecuteClass()
{

}

ExecuteClass::~ExecuteClass()
{

}

int ExecuteClass::chooser(int cmdID, String cmdName)
{
  if (cmdID < 11)
  {
    //команды для DipLink
  }
  else if (cmdID < 31)
  {
    //команды для движков
    switch (cmdID)
    {
      case 11:
        return 0;
      case 12:
        return 0;
      case 13:
        return 0;
    }
  }
  else if (cmdID < 61)
  {
    //команды для списка
  }

  return 0;
}
