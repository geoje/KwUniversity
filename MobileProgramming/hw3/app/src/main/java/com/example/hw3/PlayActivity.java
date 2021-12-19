package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.Locale;

public class PlayActivity extends AppCompatActivity {
    boolean isPlaying = false;

    private IMusicService mBinder;
    private ServiceConnection mConnection;

    ImageView ivPlay;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);

        // 인텐트에서 뮤직 아이템 받기
        MusicItem item = getIntent().getParcelableExtra("MUSIC_ITEM");
        int index = getIntent().getIntExtra("INDEX", 0);
        UpdateMusicInfo(item);

        // 바운드 서비스 연결 후 자동으로 음악 재생
        ivPlay = findViewById(R.id.ivPlay);
        Intent serviceIntent = new Intent(this, MusicService.class);
        mConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                mBinder = IMusicService.Stub.asInterface(service);
                try {
                    mBinder.Play(index);
                    isPlaying = true;
                    ivPlay.setImageResource(R.drawable.ic_baseline_pause_24);
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {

            }
        };
        bindService(serviceIntent, mConnection, BIND_AUTO_CREATE);

        // 이미지 버튼들 이벤트 등록
        ivPlay.setOnClickListener(v -> {
            try {
                // 중지
                if (isPlaying) {
                    isPlaying = false;
                    mBinder.Pause();

                    ivPlay.setImageResource(R.drawable.ic_baseline_play_arrow_24);
                }
                // 재생
                else {
                    isPlaying = true;
                    mBinder.Resume();

                    ivPlay.setImageResource(R.drawable.ic_baseline_pause_24);
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        });
        findViewById(R.id.ivPrev).setOnClickListener(v -> {
            try {
                UpdateMusicInfo(mBinder.Prev());
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            if (!isPlaying) {
                isPlaying = true;
                ivPlay.setImageResource(R.drawable.ic_baseline_pause_24);
            }
        });
        findViewById(R.id.ivNext).setOnClickListener(v -> {
            try {
                UpdateMusicInfo(mBinder.Next());
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            if (!isPlaying) {
                isPlaying = true;
                ivPlay.setImageResource(R.drawable.ic_baseline_pause_24);
            }
        });
    }

    @Override
    protected void onDestroy() {
        unbindService(mConnection);
        super.onDestroy();
    }

    // 앨범의 이미지, 곡이름 등을 통해 UI 업데이트
    void UpdateMusicInfo(MusicItem item) {
        ((ImageView)findViewById(R.id.ivImage)).setImageBitmap(item.getImage(this));
        ((TextView)findViewById(R.id.tvTitle)).setText(item.getTitle());
        ((TextView)findViewById(R.id.tvTime)).setText(
                String.format(Locale.KOREA, "00:00 / %s",
                        MusicItem.convertDurationToString(item.getDuration())));
    }
}