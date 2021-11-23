package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class ThreadFirstActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread_first);
        setTitle(getIntent().getStringExtra("title"));
    }
}