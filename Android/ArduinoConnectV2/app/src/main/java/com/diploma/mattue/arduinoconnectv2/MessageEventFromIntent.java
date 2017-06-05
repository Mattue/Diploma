package com.diploma.mattue.arduinoconnectv2;

/**
 * Created by Mattue on 05.06.2017.
 */

public class MessageEventFromIntent
{
    public final String messageID;
    public final String messageName;

    public MessageEventFromIntent(String messageID, String messageName)
    {
        this.messageID = messageID;
        this.messageName = messageName;
    }
}