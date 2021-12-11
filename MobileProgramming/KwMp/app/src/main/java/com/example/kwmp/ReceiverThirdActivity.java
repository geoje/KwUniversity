package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class ReceiverThirdActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_receiver_third);
        setTitle(getIntent().getStringExtra("title"));
    }
}