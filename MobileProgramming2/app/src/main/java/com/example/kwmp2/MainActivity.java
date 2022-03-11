package com.example.kwmp2;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Application;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btnWeb).setOnClickListener(view ->
                startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://www.naver.com"))));
        findViewById(R.id.btnCall).setOnClickListener(view ->
                startActivity(new Intent(Intent.ACTION_DIAL, Uri.parse("tel:911"))));
        findViewById(R.id.btnGallery).setOnClickListener(view -> {});
        findViewById(R.id.btnExit).setOnClickListener(view -> finish());
    }
}