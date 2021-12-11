package com.example.kwmp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.TextView;

public class ThreadSecondActivity extends AppCompatActivity {
    Thread countThread;
    Handler mHandler = new Handler();
    int count;

    TextView tvCount;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread_second);
        setTitle(getIntent().getStringExtra("title"));

        tvCount = findViewById(R.id.tvCount);
        countThread = new Thread(() -> {
            while (true) {
                try {
                    Thread.sleep(1000);
                    count++;

                    // 메세지 생성 후 옵테인 호출
//                    mHandler.sendMessage(Message.obtain(mHandler, () -> tvCount.setText(Integer.toString(count))));

                    // 해당 뷰의 핸들러 이용
//                    tvCount.post(() -> tvCount.setText(Integer.toString(count)));

                    // 엑티비티의 핸들러 이용 (여러 뷰 컨트롤 가능)
                    ThreadSecondActivity.this.runOnUiThread(() -> {
                       tvCount.setText(Integer.toString(count));
                    });
                } catch (Exception e) {}
            }
        });
        countThread.start();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (countThread != null && countThread.isAlive())
            countThread.interrupt();
    }
}