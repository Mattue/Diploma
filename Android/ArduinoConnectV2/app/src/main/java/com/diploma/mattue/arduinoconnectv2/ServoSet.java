package com.diploma.mattue.arduinoconnectv2;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class ServoSet extends AppCompatActivity
{

    Button btLeft, btRight;
    TextView tvServoValue;
    int straightValue = 90;
    String messageFromMain = "0";
    String messageToMain = "";

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_servo_set);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        EventBus.getDefault().register(this);

        btLeft = (Button) findViewById(R.id.btLeft);
        btRight = (Button) findViewById(R.id.btRight);
        tvServoValue = (TextView) findViewById(R.id.tvServoValue);

        tvServoValue.setText(messageFromMain);

        //sendMessage("020", "GIVE_SERVO_VALUE");
        //enableUI(false);
    }

    void enableUI(boolean messageGot)
    {
        btLeft.setEnabled(messageGot);
        btRight.setEnabled(messageGot);
    }

    private void sendMessage(String messageID, String messageName)
    {
        EventBus.getDefault().post(new MessageEventFromIntent(messageID, messageName));
    }

    public void onLeftClick(View v)
    {
        straightValue -= 10;
        sendMessage("014", "NEW_STRAIGHT_VALUE_" + straightValue);
        //enableUI(false);
    }

    public void onRightClick(View v)
    {
        straightValue += 10;
        sendMessage("014", "NEW_STRAIGHT_VALUE_" + straightValue);
        //enableUI(false);
    }

    public int getServoNumValue(String command)
    {
        int degree = 0;

        int i = messageFromMain.length() - 1;

        while (messageFromMain.charAt(i) != '_')
        {
          i--;
        }

        try
        {
            degree = Integer.parseInt(messageFromMain.substring(i+1));
        }
        catch (NumberFormatException e)
        {
            tvServoValue.setText("NUMBER FORMAT EXCEPTION");
        }

        return degree;
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onEvent(MessageEventFromMain event)
    {
        messageFromMain = event.message;
        straightValue = getServoNumValue(messageFromMain);
        tvServoValue.setText("" + straightValue);
        //enableUI(true);
    };
}
