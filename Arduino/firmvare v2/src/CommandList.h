#include "Arduino.h"

class CommandList
{
private:
  struct listElem
  {
      int commandID;
      String commandName;
      listElem* prev;
      listElem* next;
  };
  listElem* head;
  listElem* tail;
  int size;

  int parseCommandID(String command);
  String parseCommandName(String command);
  void createList(String command);

public:
  CommandList ();
  ~CommandList();
  int addFirst(String command);
  int addLast(String command);
  int removeFirst();
  int removeLast();
  int getCommandID();
  String getCommandName();
  int getSize();
  int clearList();
};
