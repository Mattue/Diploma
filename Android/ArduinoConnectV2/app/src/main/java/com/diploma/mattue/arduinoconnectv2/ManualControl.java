package com.diploma.mattue.arduinoconnectv2;

import android.os.Bundle;
import android.support.design.internal.ParcelableSparseArray;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class ManualControl extends AppCompatActivity {

    Button btForward, btBackward, btStop, btLeft, btRight, btStraight;
    TextView tvLastCommand;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_manual_control);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        //EventBus.getDefault().register(this);

        btForward = (Button) findViewById(R.id.btFrvd);
        btBackward = (Button) findViewById(R.id.btBackward);
        btStop = (Button)findViewById(R.id.btStop);
        btLeft = (Button) findViewById(R.id.btLeft);
        btRight = (Button) findViewById(R.id.btRight);
        btStraight = (Button) findViewById(R.id.btStraight);

        tvLastCommand = (TextView) findViewById(R.id.tvLastCommand);
    }

    @Override
    protected void onPause()
    {
        sendMessage("019", "STOP_WHEELS");
        super.onPause();
    }

    @Override
    public void onResume()
    {
        super.onResume();
    }

    @Override
    public void onStart()
    {
        super.onStart();
        EventBus.getDefault().register(this);
    }

    @Override
    protected void onStop()
    {
        super.onStop();
        EventBus.getDefault().unregister(this);
    }


    public void onForwardClick(View v)
    {
        sendMessage("016", "START_WHEELS_FRWD");
        enableUI(false);
        whait1sec();
        tvLastCommand.setText("016_START_WHEELS_FRWD");
        enableUI(true);
    }

    public void onBackwardClick(View v)
    {
        sendMessage("017", "START_WHEELS_BCKW");
        enableUI(false);
        whait1sec();
        tvLastCommand.setText("017_START_WHEELS_BCKW");
        enableUI(true);
    }

    public void onStopClick(View v)
    {
        sendMessage("019", "STOP_WHEELS");
        enableUI(false);
        whait1sec();
        tvLastCommand.setText("018_STOP_WHEELS");
        enableUI(true);
    }

    public void onLeftClick(View v)
    {
        sendMessage("012", "TURN_LEFT");
        enableUI(false);
        whait1sec();
        tvLastCommand.setText("012_TURN_LEFT");
        enableUI(true);
    }

    public void onRightClick(View v)
    {
        sendMessage("013", "TURN_RIGHT");
        enableUI(false);
        whait1sec();
        tvLastCommand.setText("013_TURN_RIGHT");
        enableUI(true);
    }

    public void onStraightClick(View v)
    {
        sendMessage("011", "TURN_STRAIGHT");
        enableUI(false);
        whait1sec();
        tvLastCommand.setText("011_TURN_STRAIGHT");
        enableUI(true);
    }

    private void whait1sec()
    {
        try
        {
            Thread.sleep(1000);
        }
        catch (InterruptedException e)
        {

        }
    }

    void enableUI(boolean messageGot)
    {
        btForward.setEnabled(messageGot);
        btBackward.setEnabled(messageGot);
        btStop.setEnabled(messageGot);
        btLeft.setEnabled(messageGot);
        btRight.setEnabled(messageGot);
        btStraight.setEnabled(messageGot);
    }

    private void sendMessage(String messageID, String messageName)
    {
        Log.d("Sub debug", "message posted");
        EventBus.getDefault().post(new MessageEventFromIntent(messageID, messageName));
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onEvent(MessageEventFromMain event)
    {

    }
}
