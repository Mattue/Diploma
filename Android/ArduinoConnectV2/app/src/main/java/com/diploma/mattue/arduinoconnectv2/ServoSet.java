package com.diploma.mattue.arduinoconnectv2;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class ServoSet extends AppCompatActivity
{

    TextView tvHello;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_servo_set);

        tvHello = (TextView) findViewById(R.id.textView2);

        setContentView(R.layout.activity_servo_set);
    }
}
