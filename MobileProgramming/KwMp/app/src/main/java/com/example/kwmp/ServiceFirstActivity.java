package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

public class ServiceFirstActivity extends AppCompatActivity {
    Intent intent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_service_first);
        setTitle(getIntent().getStringExtra("title"));

        findViewById(R.id.btnStart).setOnClickListener(o -> {
            startService(intent = new Intent(this, CountService.class));
        });
        findViewById(R.id.btnStop).setOnClickListener(o -> {
            if (intent != null) {
                stopService(intent);
                intent = null;
            }
        });
        findViewById(R.id.btnShow).setOnClickListener(o -> {

        });
    }
}