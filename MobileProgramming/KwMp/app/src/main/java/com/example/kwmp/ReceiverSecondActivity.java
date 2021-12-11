package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.BatteryManager;
import android.os.Bundle;
import android.widget.TextView;

public class ReceiverSecondActivity extends AppCompatActivity {
    BroadcastReceiver receiverScreenOn, receiverScreenOff, receiverBattery;
    TextView tvLog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receiver_second);
        setTitle(getIntent().getStringExtra("title"));

        tvLog = findViewById(R.id.tvLog);
        
        // 화면 켜짐
        registerReceiver(receiverScreenOn = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                addLog("화면 켜짐");
            }
        }, new IntentFilter(Intent.ACTION_SCREEN_ON));

        // 화면 꺼짐
        registerReceiver(receiverScreenOff = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                addLog("화면 꺼짐");
            }
        }, new IntentFilter(Intent.ACTION_SCREEN_OFF));

        // 배터리 상태 변경
        registerReceiver(receiverBattery = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                String text = "";

                switch (intent.getIntExtra(BatteryManager.EXTRA_STATUS, BatteryManager.BATTERY_STATUS_UNKNOWN)) {
                    case BatteryManager.BATTERY_STATUS_CHARGING:
                        text += "배터리 충전중임";
                        break;
                    case BatteryManager.BATTERY_STATUS_NOT_CHARGING:
                        text += "배터리 충전중 아님";
                        break;
                    case BatteryManager.BATTERY_STATUS_DISCHARGING:
                        text += "배터리 방전중";
                        break;
                    case BatteryManager.BATTERY_STATUS_FULL:
                        text += "배터리 최대 충전됨";
                        break;
                    case BatteryManager.BATTERY_STATUS_UNKNOWN:
                        text += "배터리 상태 모름";
                        break;
                }

                int scale = intent.getIntExtra(BatteryManager.EXTRA_SCALE, 100);
                int level = intent.getIntExtra(BatteryManager.EXTRA_LEVEL, 0);
                text += String.format(" (%d%%)", level * 100 / scale);

                addLog(text);
            }
        }, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
    }

    @Override
    protected void onDestroy() {
        unregisterReceiver(receiverScreenOn);
        unregisterReceiver(receiverScreenOff);
        unregisterReceiver(receiverBattery);
        super.onDestroy();
    }
    
    void addLog(String text) {
        tvLog.setText(tvLog.getText() + "\n" + text);
    }
}