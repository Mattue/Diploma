package com.diploma.mattue.arduinoconnectv2;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import org.greenrobot.eventbus.EventBus;
import org.greenrobot.eventbus.Subscribe;
import org.greenrobot.eventbus.ThreadMode;

public class CommandList extends AppCompatActivity {

    String messageFromMain;
    Button btSend, btDelete, btStop, btClear, btStart;
    TextView tvComands;
    Spinner spComands;

    String[] data = {"Влево", "Вправо", "Прямо", "Запустить прямо", "Запустить обратно", "Остановить", "Работать 5 секунд"};

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_command_list);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        EventBus.getDefault().register(this);

        btSend = (Button) findViewById(R.id.btSend);
        btDelete = (Button) findViewById(R.id.btDelete);
        btStop = (Button) findViewById(R.id.btStop);
        btClear = (Button) findViewById(R.id.btClear);
        btStart = (Button) findViewById(R.id.btStart);

        tvComands = (TextView) findViewById(R.id.tvComands);

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
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent)
            {

            }
        });
    }

    @Subscribe(threadMode = ThreadMode.MAIN)
    public void onEvent(MessageEventFromMain event)
    {
        messageFromMain = event.message;
    };

    public void onDeleteClick(View v)
    {
        sendMessage("032", "DELETE_COMAND");
    }

    public void onClearClick(View v)
    {
        sendMessage("033", "CLEAR_LIST");
    }

    public void onStopClick(View v)
    {
        sendMessage("008", "STOP_EXEC_COMAND_LIST");
    }

    public void onStartClick(View v)
    {
        sendMessage("007", "EXEC_COMAND_LIST");
    }

    public void onSendClick(View v)
    {

    }

    void enableUI(boolean value)
    {
        btSend.setEnabled(value);
        btDelete.setEnabled(value);
        btClear.setEnabled(value);
        btStart.setEnabled(value);
        btStop.setEnabled(!value);
    }

    private void sendMessage(String messageID, String messageName)
    {
        EventBus.getDefault().post(new MessageEventFromIntent(messageID, messageName));
    }

}
