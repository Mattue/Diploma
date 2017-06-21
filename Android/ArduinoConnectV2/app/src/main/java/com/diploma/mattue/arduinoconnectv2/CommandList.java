package com.diploma.mattue.arduinoconnectv2;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;
import org.w3c.dom.Text;

import java.util.ArrayList;

public class CommandList extends AppCompatActivity {

    String messageFromMain;
    Button btSend, btDelete, btStop, btClear, btStart;
    TextView tvComands, tvAnswers;
    Spinner spComands;

    String[] data = {"Влево", "Вправо", "Прямо", "Запустить прямо", "Запустить обратно", "Остановить", "Работать 5 секунд"};
    ArrayList<String> comands;

    int currentCommand = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_command_list);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        //EventBus.getDefault().register(this);

        comands = new ArrayList<String>();

        btSend = (Button) findViewById(R.id.btSend);
        btDelete = (Button) findViewById(R.id.btDelete);
        btStop = (Button) findViewById(R.id.btStop);
        btClear = (Button) findViewById(R.id.btClear);
        btStart = (Button) findViewById(R.id.btStart);

        tvComands = (TextView) findViewById(R.id.tvComands);
        tvAnswers = (TextView) findViewById(R.id.tvAnswers);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, data);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        spComands = (Spinner) findViewById(R.id.spComands);
        spComands.setAdapter(adapter);

        spComands.setPrompt("Команды");

        spComands.setSelection(0);

        spComands.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
            {
                //Toast.makeText(getBaseContext(), "Position = " + position, Toast.LENGTH_SHORT).show();
                currentCommand = position;
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent)
            {

            }
        });
    }

    @Override
    public void onResume()
    {
        super.onResume();
        EventBus.getDefault().register(this);
    }

    @Override
    public void onPause()
    {
        super.onPause();
        EventBus.getDefault().unregister(this);
    }


    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onEvent(MessageEventFromMain event)
    {
        messageFromMain = event.message;

        if (messageFromMain.contains("STATUS"))
        {
            tvAnswers.append(messageFromMain);
            tvAnswers.append("\n");
            comands.remove(0);
            printComands();
        }

        if (messageFromMain.contains("STOP_EXEC"))
        {
            tvAnswers.append(messageFromMain);
            comands.clear();
            printComands();
            enableUI(true);
        }
    }

    @Override
    protected void onDestroy()
    {
        this.finish();
        super.onDestroy();
    }

    public void onDeleteClick(View v)
    {
        sendMessage("032", "DELETE_COMAND");

        disableUI();

        try
        {
            Thread.sleep(1000);
        }
        catch(InterruptedException e)
        {

        }

        enableUI(true);

        comands.remove(comands.size() - 1);
        printComands();
    }

    public void onClearClick(View v)
    {
        sendMessage("033", "CLEAR_LIST");

        disableUI();

        try
        {
            Thread.sleep(1000);
        }
        catch(InterruptedException e)
        {

        }

        enableUI(true);

        comands.clear();
        printComands();
    }

    public void onStopClick(View v)
    {
        sendMessage("008", "STOP_EXEC_COMAND_LIST");

        disableUI();

        try
        {
            Thread.sleep(1000);
        }
        catch(InterruptedException e)
        {

        }

        enableUI(true);

        comands.clear();
        printComands();
    }

    public void onStartClick(View v)
    {
        if (comands.size() != 0)
        {
            tvAnswers.setText("");

            sendMessage("007", "EXEC_COMAND_LIST");

            disableUI();

            try
            {
                Thread.sleep(1000);
            }
            catch(InterruptedException e)
            {

            }

            enableUI(false);
        }
    }

    public void onSendClick(View v)
    {
        enableUI(false);
        switch (currentCommand)
        {
            case 0:
            {
                sendMessage("031", "012_TURN_LEFT");
                comands.add("012_TURN_LEFT");
                break;
            }
            case 1:
            {
                sendMessage("031", "013_TURN_RIGHT");
                comands.add("013_TURN_RIGHT");
                break;
            }
            case 2:
            {
                sendMessage("031", "011_TURN_STRAIGHT");
                comands.add("011_TURN_STRAIGHT");
                break;
            }
            case 3:
            {
                sendMessage("031", "016_START_WHEELS_FRWD");
                comands.add("016_START_WHEELS_FRWD");
                break;
            }
            case 4:
            {
                sendMessage("031", "017_START_WHEELS_BCKW");
                comands.add("017_START_WHEELS_BCKW");
                break;
            }
            case 5:
            {
                sendMessage("031", "019_STOP_WHEELS");
                comands.add("019_STOP_WHEELS");
                break;
            }
            case 6:
            {
                sendMessage("031", "023_WAIT_10");
                comands.add("023_WAIT_10");
                break;
            }
        }

        disableUI();

        try
        {
            Thread.sleep(1000);
        }
        catch (InterruptedException e)
        {

        }

        enableUI(true);
        printComands();
    }

    void printComands()
    {
        tvComands.setText("");
        for (int i = 0; i < comands.size(); i++)
        {
            tvComands.append(comands.get(i));
            tvComands.append("\n");
        }
    }

    void enableUI(boolean value)
    {
        btSend.setEnabled(value);
        btDelete.setEnabled(value);
        btClear.setEnabled(value);
        btStart.setEnabled(value);
        spComands.setEnabled(value);
        btStop.setEnabled(!value);
    }

    void disableUI()
    {
        btSend.setEnabled(false);
        btDelete.setEnabled(false);
        btClear.setEnabled(false);
        btStart.setEnabled(false);
        btStop.setEnabled(false);
        spComands.setEnabled(false);
    }

    private void sendMessage(String messageID, String messageName)
    {
        EventBus.getDefault().post(new MessageEventFromIntent(messageID, messageName));
    }

}
