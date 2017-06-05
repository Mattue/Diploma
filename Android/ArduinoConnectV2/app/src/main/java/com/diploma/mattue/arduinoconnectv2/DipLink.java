package com.diploma.mattue.arduinoconnectv2;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.widget.Toast;

import java.lang.ref.WeakReference;
import java.util.Set;

/**
 * Created by Mattue on 05.06.2017.
 */

public class DipLink
{
    public DipLink()
    {
        connectionEnabled = false;
    }

    public int enableConnection()
    {
        if (!connectionEnabled)
        {
            //enable connection here
        }
        else
        {
            return 0; //already connected
        }

        return 2; //major error
    }

    public int chekConnection()
    {
        if (connectionEnabled)
        {
            //check connection here
        }
        else
        {
            return 1; //connection break
        }

        return 2; //major error
    }

    public int reconnect()
    {
        //close connection here

        return enableConnection();
    }

    public String readMessage(String message)
    {
        int msgLen = 0;
        String line = message;
        String resMessage = "";
        line.trim();

        String buf = "";

        //get package start info
        buf = line.substring(0,1);
        if(!buf.equalsIgnoreCase("55"))
        {
            return "NOT_PAKAGE";
        }

        //get msgLen info
        buf = line.substring(2,4);
        try
        {
            msgLen = Integer.parseInt(buf);
        }
        catch(NumberFormatException e)
        {
            return "MSG_LEN_FORMAT_ERROR";
        }

        //get msgID info
        buf = line.substring(5, 7);
        try
        {
            Integer.parseInt(buf);
        }
        catch(NumberFormatException e)
        {
            return "MSG_ID_FORMAT_ERROR";
        }
        resMessage = resMessage + buf + '_';

        //get msg info
        buf = line.substring(8, msgLen);
        resMessage += buf;

        //get packageLen
        buf = line.substring(msgLen + 1);
        try
        {
            Integer.parseInt(buf);
        }
        catch(NumberFormatException e)
        {
            return "PACKAGE_LEN_ERROR";
        }

        //check for package integrity
        if (Integer.parseInt(buf) != message.length())
        {
            return "PACKAGE_BROKEN";
        }

        return resMessage;
    }

    public String writeMessage(String msgID, String message)
    {
        String messagePackage = "55";

        messagePackage = messagePackage + zeroAdd(message) + msgID + message;
        messagePackage += (messagePackage.length() + getNumLen(messagePackage.length()));
        messagePackage.toUpperCase();

        return messagePackage;
    }

    public String createHeartBeatMessage()
    {
        return writeMessage("000", "BEAT");
    }

    private int getNumLen(int length)
    {
        int buf = length;

        int count = (buf == 0) ? 1 : 0;
        while (buf != 0)
        {
            count ++;
            buf /= 10;
        }

        return count;
    }

    public int getCommandID(String commamd)
    {
        String commandID;

        commandID = commamd.substring(0, 2);
        try
        {
            return Integer.parseInt(commandID);
        }
        catch (NumberFormatException e)
        {
            return 1; //not numeric value
        }
    }

    public String getCommandMsg(String command)
    {
        return command.substring(4);
    }

    //определяет длину текста "BEAT" и выдает длину этого текста в нулями в переди
    private String zeroAdd(String number)
    {
        int count = getNumLen(number.length());
        String resString = "";

        switch (count)
        {
            case 1:
                resString = resString + "00" + number.length();
                break;
            case 2:
                resString = resString + '0' + number.length();
                break;
            default:
                break;
        }

        return resString;
    }

    private boolean connectionEnabled;
}
