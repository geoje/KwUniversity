package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Locale;

public class PlayActivity extends AppCompatActivity {
    ArrayList<MusicItem> items;
    int position;

    private IMusicService mBinder;
    private ServiceConnection mConnection;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);

        // 인텐트에서 뮤직 아이템 받기
        items = getIntent().getParcelableArrayListExtra("MUSIC_ITEMS");
        position = getIntent().getIntExtra("POSITION", 0);
        MusicItem item = items.get(position);

        ((ImageView)findViewById(R.id.ivImage)).setImageBitmap(item.getImage(this));
        ((TextView)findViewById(R.id.tvTitle)).setText(item.getTitle());
        ((TextView)findViewById(R.id.tvTime)).setText(
                String.format(Locale.KOREA, "00:00 / %s",
                        convertDurationToString(item.getDuration())));

        // 바운드 서비스 연결
        mConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                mBinder = IMusicService.Stub.asInterface(service);
                try {
                    mBinder.Start(item.getFilename());
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {

            }
        };
        Intent serviceIntent = new Intent("com.example.hw3.service.MUSIC");
        bindService(serviceIntent, mConnection, BIND_AUTO_CREATE);

        // 이미지 버튼들 이벤트 등록
        findViewById(R.id.ivPlay).setOnClickListener(v -> {
            try {
                mBinder.Start(item.getFilename());
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        });
        findViewById(R.id.ivPrev).setOnClickListener(v -> {});
        findViewById(R.id.ivNext).setOnClickListener(v -> {});
    }

    @Override
    protected void onDestroy() {
        unbindService(mConnection);
        super.onDestroy();
    }

    // 분 까지만
    String convertDurationToString(long duration) {
        duration /= 1000;

        long s = duration % 60;
        long m = duration / 60 % 60;

        return String.format(Locale.KOREA, "%02d:%02d", m, s);
    }
}