#include "Arduino.h"

class DipLink
{
  private:
    int getNumLen(int number);
    String zeroAdd(String number);

  public:
    DipLink();
    ~DipLink();
    String readMessage(String input);
    String writeMessage(String input, String msgID);
    String createHeartBeatMessage();
};
