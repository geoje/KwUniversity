package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ListView lvMain = findViewById(R.id.lvMain);
        ListViewAdapter adapter = new ListViewAdapter();

        lvMain.setAdapter(adapter);
        lvMain.setOnItemClickListener((parent, view, position, id) -> {
            final ListViewItem item = (ListViewItem) adapter.getItem(position);
            if (item.getIntent() != null)
                startActivity(item.getIntent());
        });

        adapter.addItem("14장 - Thread 1", "Thread 익명 클래스 사용 및 ANR 확인", new Intent(this, ThreadFirstActivity.class));
        adapter.addItem("14장 - Thread 2", "Looper, MessageQueue, Handler 사용", null);
        adapter.addItem("14장 - Thread 3", "AsyncTask, CountDownTimer, TimerTask, HandlerTask 사용", null);
        adapter.addItem("15장 - Broadcast Receiver 1", "Intent를 만들고 sendBroadcast, BroadcastReceiver 구현, 정적 및 동적 리시버 동작 제한", null);
        adapter.addItem("15장 - Broadcast Receiver 2", "리시버의 동작 시간 제한, 배터리 감시", null);
        adapter.addItem("15장 - Broadcast Receiver 3", "IntentFilter, LocalBroadcastManager 사용", null);
        adapter.addItem("18장 - Service 1", "Service를 상속받아 클래스를 만들고 startService 실행", null);
        adapter.addItem("18장 - Service 2", "아직 배우지 않음", null);
        adapter.addItem("18장 - Service 3", "아직 배우지 않음", null);
    }
}