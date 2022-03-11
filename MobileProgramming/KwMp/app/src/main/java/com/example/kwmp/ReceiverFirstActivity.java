package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.widget.Toast;

public class ReceiverFirstActivity extends AppCompatActivity {
    BroadcastReceiver receiver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receiver_first);
        setTitle(getIntent().getStringExtra("title"));

        // 정적 리시버 송신
        findViewById(R.id.btnBroadcastStatic).setOnClickListener(o -> {
            Intent intent = new Intent();
            intent.setAction("com.example.kwmp.action.FILE_DOWNLOADED_STATIC");
            intent.putExtra("FILE_NAME", "ygh.png");
            sendBroadcast(intent);

            Toast.makeText(ReceiverFirstActivity.this, "사실상 작동 안함", Toast.LENGTH_SHORT).show();
        });
        // 정적 리시버 송신
        findViewById(R.id.btnBroadcastDynamic).setOnClickListener(o -> {
            Intent intent = new Intent();
            intent.setAction("com.example.kwmp.action.FILE_DOWNLOADED_DYNAMIC");
            intent.putExtra("FILE_NAME", "ygh.png");
            sendBroadcast(intent);

            Toast.makeText(ReceiverFirstActivity.this, "사실상 작동 안함", Toast.LENGTH_SHORT).show();
        });

        // 동적 리시버 수신
        receiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                Toast.makeText(
                        context,
                        "Receiver: FILE_DOWNLOADED\n" + intent.getStringExtra("FILE_NAME"),
                        Toast.LENGTH_LONG)
                        .show();
            }
        };
        IntentFilter filter = new IntentFilter();
        filter.addAction("com.example.kwmp.action.FILE_DOWNLOADED_DYNAMIC");
        registerReceiver(receiver, filter);
    }

    @Override
    protected void onDestroy() {
        unregisterReceiver(receiver);
        super.onDestroy();
    }
}