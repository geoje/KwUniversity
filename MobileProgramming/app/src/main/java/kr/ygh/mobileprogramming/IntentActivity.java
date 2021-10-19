package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;

public class IntentActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_intent);

        findViewById(R.id.btnHw1).setOnClickListener(view -> {
            Intent intent = new Intent();
            intent.setComponent(new ComponentName("com.example.hw1", "com.example.hw1.MainActivity"));
            startActivity(intent);
        });
    }
}