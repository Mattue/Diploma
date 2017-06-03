#include "Arduino.h"

class CommandList
{
private:
  struct listElem
  {
      String commandID;
      String commandName;
      listElem* prev;
      listElem* next;
  };
  listElem* head;
  listElem* tail;
  int size;

  String parseCommandID(String command);
  String parseCommandName(String command);
  void createList(String command);

public:
  CommandList ();
  ~CommandList();
  int addFirst(String command);
  int addLast(String command);
  int removeFirst();
  int removeLast();
  String getCommandID();
  String getCommandName();
  int getSize();
};
