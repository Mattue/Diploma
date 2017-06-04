#include "Arduino.h"

class DipLink
{
  private:
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
    String sendMessage(String input);
    String getMessage();
};
