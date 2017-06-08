package com.diploma.mattue.arduinoconnectv2;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

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

        btLeft = (Button) findViewById(R.id.btLeft);
        btRight = (Button) findViewById(R.id.btLeft);
        tvServoValue = (TextView) findViewById(R.id.tvServoValue);
    }

    @Override
    protected void onStart()
    {
        super.onStart();

        tvServoValue.setText("" + straightValue);

        EventBus.getDefault().register(this);

        try
        {
            Thread.sleep(1000);
        }
        catch (InterruptedException e)
        {

        }

        sendMessage("020", "GIVE_SERVO_VALUE");
        enableUI(false);
    }

    @Override
    protected void onPause()
    {
        super.onPause();

    }

    protected void onSaveInstanceState(Bundle outState)
    {
        outState.putInt("value", straightValue);
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState)
    {
        super.onRestoreInstanceState(savedInstanceState);
        straightValue = savedInstanceState.getInt("value");
        enableUI(true);
    }

    @Override
    protected void onDestroy()
    {
        EventBus.getDefault().unregister(this);
        super.onDestroy();
    }

    /*@Override
    public void finish()
    {
        super.finish();
    }*/

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
        straightValue += 1;
        if (straightValue > 110)
        {
            Toast.makeText(this, "Угол не может быть больше 110",Toast.LENGTH_LONG).show();
        }
        sendMessage("014", "NEW_STRAIGHT_VALUE_" + straightValue);
        enableUI(false);
    }

    public void onRightClick(View v)
    {
        straightValue -= 1;
        if (straightValue < 70)
        {
            Toast.makeText(this, "Угол не может быть меньше 70",Toast.LENGTH_LONG).show();
        }
        sendMessage("014", "NEW_STRAIGHT_VALUE_" + straightValue);
        enableUI(false);
    }

    public int getServoNumValue(String command)
    {
        int degree = 0;

        int i = command.length() - 1;

        while (command.charAt(i) != '_')
        {
          i--;
        }

        try
        {
            degree = Integer.parseInt(command.substring(i+1));
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
        //tvServoValue.setText(messageFromMain);
        enableUI(true);
    };
}
