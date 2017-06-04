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
    String readMessage(String input);
    String writeMessage(String input, String msgID);
    String createHeartBeatMessage();
    int sendMessage(String message);
    String getMessage();
};
