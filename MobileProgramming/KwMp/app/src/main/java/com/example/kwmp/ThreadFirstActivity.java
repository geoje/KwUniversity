package com.example.kwmp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.widget.TextView;
import android.widget.Toast;

public class ThreadFirstActivity extends AppCompatActivity {
    TextView tvCall, tvCamera, tvCount;
    Thread countThread;
    Handler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread_first);
        setTitle(getIntent().getStringExtra("title"));

        // 1
//        Thread t = new Worker();
//        t.start();

        // 2
//        Thread t = new Thread() {
//            @Override
//            public void run() {
//                super.run();
//            }
//        }
//        t.start();

        // 3
//        Thread t = new Worker2();
//        t.start();

        // 4
//        new Thread(new Worker2());
//        new Thread(new Runnable() { // Runnable 생략 가능
//            @Override
//            public void run() {
//
//            }
//        }).start();
//        new Thread(() -> { // 간단한 람다식 표현
//
//        }).start();

        // ANR 확인
//        try {
//            Thread.sleep(20000);
//        } catch (Exception e) {}

        // 런타임 권한 요청
        tvCall = findViewById(R.id.tvCall);
        tvCamera = findViewById(R.id.tvCamera);
        findViewById(R.id.btnPermission).setOnClickListener(o -> {
            if (checkSelfPermission(Manifest.permission.CALL_PHONE) != PackageManager.PERMISSION_GRANTED ||
                    checkSelfPermission(Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED)
                ActivityCompat.requestPermissions(
                        ThreadFirstActivity.this,
                        new String[] {Manifest.permission.CALL_PHONE, Manifest.permission.CAMERA},
                        1);
        });

        // 작업 스레드에서 화면 그리기
        mHandler = new Handler();
        tvCount = findViewById(R.id.tvCount);
        countThread = new Thread(() -> {
            try {
                int num = 0;
                while (true) {
                    Thread.sleep(1000);
                    int finalNum = ++num;
                    mHandler.post(() -> tvCount.setText(Integer.toString(finalNum)));
                }
            } catch(Exception e) {}

        });
        countThread.start();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (countThread != null && countThread.isAlive())
            countThread.interrupt();
    }

    class Worker extends Thread {
        @Override
        public void run() {
            super.run();
        }
    }

    class Worker2 implements Runnable {
        @Override
        public void run() {

        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        for (int i = 0; i < grantResults.length; i++)
            if (permissions[i].equals(Manifest.permission.CALL_PHONE)) {
                tvCall.setText(String.format("전화 권한을 %s 하였습니다.", grantResults[i] == PackageManager.PERMISSION_GRANTED ? "승인" : "거절"));
            }
            else if (permissions[i].equals(Manifest.permission.CAMERA)) {
                tvCamera.setText(String.format("카메라 사용 권한을 %s 하였습니다.", grantResults[i] == PackageManager.PERMISSION_GRANTED ? "승인" : "거절"));
            }
    }
}