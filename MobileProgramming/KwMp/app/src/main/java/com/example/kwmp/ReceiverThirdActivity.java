package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.widget.TextView;

public class ReceiverThirdActivity extends AppCompatActivity {
    String ACTION = "com.example.kwmp.action.LOCAL_BROADCAST";

    TextView tvCount;
    int count = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receiver_third);
        setTitle(getIntent().getStringExtra("title"));

        // 송신 등록
        findViewById(R.id.btnBroadcast).setOnClickListener(o ->
                LocalBroadcastManager
                        .getInstance(this)
                        .sendBroadcast(new Intent(ACTION))
        );

        // 수신 등록
        tvCount = findViewById(R.id.tvCount);
        LocalBroadcastManager.getInstance(this).registerReceiver(new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                tvCount.setText(Integer.toString(++count));
            }
        }, new IntentFilter(ACTION));
    }
}