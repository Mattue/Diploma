package com.example.mattue.arduinoconnect;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.os.Handler;
import android.widget.TextView;

import java.lang.ref.WeakReference;
import java.util.Set;


public class MainActivity extends AppCompatActivity
{
    Button btOn, btOff, bt_left, bt_right, btStraight;
    TextView tvRead;

    /*
     * Notifications from UsbService will be received here.
     */
    private final BroadcastReceiver mUsbReceiver = new BroadcastReceiver()
    {
        @Override
        public void onReceive(Context context, Intent intent)
        {
            switch (intent.getAction())
            {
                case UsbService.ACTION_USB_PERMISSION_GRANTED: // USB PERMISSION GRANTED
                    Toast.makeText(context, "USB Ready", Toast.LENGTH_SHORT).show();
                    setEnabledUi(true);
                    break;
                case UsbService.ACTION_USB_PERMISSION_NOT_GRANTED: // USB PERMISSION NOT GRANTED
                    Toast.makeText(context, "USB Permission not granted", Toast.LENGTH_SHORT).show();
                    break;
                case UsbService.ACTION_NO_USB: // NO USB CONNECTED
                    Toast.makeText(context, "No USB connected", Toast.LENGTH_SHORT).show();
                    break;
                case UsbService.ACTION_USB_DISCONNECTED: // USB DISCONNECTED
                    Toast.makeText(context, "USB disconnected", Toast.LENGTH_SHORT).show();
                    setEnabledUi(false);
                    break;
                case UsbService.ACTION_USB_NOT_SUPPORTED: // USB NOT SUPPORTED
                    Toast.makeText(context, "USB device not supported", Toast.LENGTH_SHORT).show();
                    break;
                default:
                    break;
            }
        }
    };

    private UsbService usbService;
    private MyHandler mHandler;
    private final ServiceConnection usbConnection = new ServiceConnection()
    {
        @Override
        public void onServiceConnected(ComponentName arg0, IBinder arg1)
        {
            usbService = ((UsbService.UsbBinder) arg1).getService();
            usbService.setHandler(mHandler);
        }

        @Override
        public void onServiceDisconnected(ComponentName arg0)
        {
            usbService = null;
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHandler = new MyHandler(this);

        btOn = (Button) findViewById(R.id.btOn);
        btOff = (Button) findViewById(R.id.btOff);
        bt_left = (Button) findViewById(R.id.bt_left);
        bt_right = (Button) findViewById(R.id.bt_right);
        btStraight = (Button) findViewById(R.id.btStraight);
        tvRead = (TextView) findViewById(R.id.tvRead);

        setEnabledUi(false);
    }

    private void setEnabledUi(boolean bConnected)
    {
        if (bConnected)
        {
            btOn.setEnabled(true);
            btOff.setEnabled(true);
            bt_left.setEnabled(true);
            bt_right.setEnabled(true);
            btStraight.setEnabled(true);
            tvRead.setEnabled(true);
        }
        else
        {
            btOn.setEnabled(false);
            btOff.setEnabled(false);
            bt_left.setEnabled(false);
            bt_right.setEnabled(false);
            btStraight.setEnabled(false);
            tvRead.setEnabled(false);
        }
    }

    @Override
    public void onResume()
    {
        super.onResume();
        setFilters();  // Start listening notifications from UsbService
        startService(UsbService.class, usbConnection, null); // Start UsbService(if it was not started before) and Bind it
    }

    @Override
    public void onPause()
    {
        super.onPause();
        unregisterReceiver(mUsbReceiver);
        unbindService(usbConnection);
    }

    private void startService(Class<?> service, ServiceConnection serviceConnection, Bundle extras)
    {
        if (!UsbService.SERVICE_CONNECTED)
        {
            Intent startService = new Intent(this, service);
            if (extras != null && !extras.isEmpty())
            {
                Set<String> keys = extras.keySet();
                for (String key : keys)
                {
                    String extra = extras.getString(key);
                    startService.putExtra(key, extra);
                }
            }
            startService(startService);
        }
        Intent bindingIntent = new Intent(this, service);
        bindService(bindingIntent, serviceConnection, Context.BIND_AUTO_CREATE);
    }

    private void setFilters()
    {
        IntentFilter filter = new IntentFilter();
        filter.addAction(UsbService.ACTION_USB_PERMISSION_GRANTED);
        filter.addAction(UsbService.ACTION_NO_USB);
        filter.addAction(UsbService.ACTION_USB_DISCONNECTED);
        filter.addAction(UsbService.ACTION_USB_NOT_SUPPORTED);
        filter.addAction(UsbService.ACTION_USB_PERMISSION_NOT_GRANTED);
        registerReceiver(mUsbReceiver, filter);
    }

    private static class MyHandler extends Handler
    {
        private final WeakReference<MainActivity> mActivity;

        public MyHandler(MainActivity activity)
        {
            mActivity = new WeakReference<>(activity);
        }

        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case UsbService.MESSAGE_FROM_SERIAL_PORT:
                    String data = (String) msg.obj;
                    mActivity.get().tvRead.append(data);
                    break;
                case UsbService.CTS_CHANGE:
                    Toast.makeText(mActivity.get(), "CTS_CHANGE",Toast.LENGTH_LONG).show();
                    break;
                case UsbService.DSR_CHANGE:
                    Toast.makeText(mActivity.get(), "DSR_CHANGE",Toast.LENGTH_LONG).show();
                    break;
            }
        }
    }

    public void onClickOn(View v)
    {
        String data = "on";
        if (usbService != null)  // if UsbService was correctly binded, Send data
        {
            usbService.write(data.getBytes());
        }
    }

    public void onClickOff(View v)
    {
        String data = "off";
        if (usbService != null)  // if UsbService was correctly binded, Send data
        {
            usbService.write(data.getBytes());
        }
    }

    public void onClickLeft(View v)
    {
        String data = "left";
        if (usbService != null)  // if UsbService was correctly binded, Send data
        {
            usbService.write(data.getBytes());
        }
    }

    public void onClickRight(View v)
    {
        String data = "right";
        if (usbService != null)  // if UsbService was correctly binded, Send data
        {
            usbService.write(data.getBytes());
        }
    }

    public void onClickStraight(View v)
    {
        String data = "straight";
        if (usbService != null)  // if UsbService was correctly binded, Send data
        {
            usbService.write(data.getBytes());
        }
    }
}
