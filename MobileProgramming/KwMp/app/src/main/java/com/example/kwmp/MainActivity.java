package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
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

        adapter.addItem("14장 - Thread 1", "- Thread 익명 클래스 사용\n- ANR 확인\n- 런타임 권한 요청\n- 작업 스레드에서 화면 그리기", new Intent(this, ThreadFirstActivity.class));
        adapter.addItem("14장 - Thread 2", "- Looper 사용\n- Message Queue 구조 보고 Handler 에 메세지 보내보기", new Intent(this, ThreadSecondActivity.class));
        adapter.addItem("14장 - Thread 3", "- AsyncTask 사용\n- CountDownTimer 사용\n- HandlerThread는 뭐야", new Intent(this, ThreadThirdActivity.class));
        adapter.addItem("15장 - Broadcast Receiver 1", "- 정적 리시버 BroadcastReceiver 사용\n- 동적 리시버 BroadcastReceiver 사용", new Intent(this, ReceiverFirstActivity.class));
        adapter.addItem("15장 - Broadcast Receiver 2", "- 리시버 동작 제한\n- 화면 방송 듣기\n- 배터리 상태 방송 듣기", new Intent(this, ReceiverSecondActivity.class));
        adapter.addItem("15장 - Broadcast Receiver 3", "IntentFilter, LocalBroadcastManager 사용", null);
        adapter.addItem("18장 - Service 1", "Service를 상속받아 클래스를 만들고 startService 실행", null);
        adapter.addItem("18장 - Service 2", "아직 배우지 않음", null);
        adapter.addItem("18장 - Service 3", "아직 배우지 않음", null);
    }
}