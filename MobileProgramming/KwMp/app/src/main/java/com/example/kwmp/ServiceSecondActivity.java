package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.IBinder;

public class ServiceSecondActivity extends AppCompatActivity {
    ServiceConnection mConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {

        }

        @Override
        public void onServiceDisconnected(ComponentName name) {

        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_service_second);
        setTitle(getIntent().getStringExtra("title"));

        Intent serviceIntent = new Intent("com.example.kwmp.service.CountService");
        bindService(serviceIntent, mConnection, BIND_AUTO_CREATE);
    }
}