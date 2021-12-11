package com.example.kwmp;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class BroadcastSideReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        // 정적 리시버 수신
        Toast.makeText(
                context,
                "Receiver: FILE_DOWNLOADED\n" + intent.getStringExtra("FILE_NAME"),
                Toast.LENGTH_LONG)
                .show();
    }
}
