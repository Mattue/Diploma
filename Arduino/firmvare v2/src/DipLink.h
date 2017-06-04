#include "Arduino.h"

class DipLink
{
  private:
    bool connectionEnabled;
    int getNumLen(int number);
    String zeroAdd(String number);

  public:
    DipLink();
    ~DipLink();
    int enableConnection();
    int checkConnection();
    int reconnect();
    String readMessage(String message);
    String writeMessage(String message, String msgID);
    String createHeartBeatMessage();
    int sendMessage(String message);
    String getMessage();
    int getCommandID(String command);
    String getCommandMsg(String command);
};
