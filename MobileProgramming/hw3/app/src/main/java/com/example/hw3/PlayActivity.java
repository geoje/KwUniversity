package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Locale;

public class PlayActivity extends AppCompatActivity {
    boolean isPlaying = false;
    int position;
    long duration;

    private IMusicService mBinder;
    private ServiceConnection mConnection;
    private Thread seekThread;

    ImageView ivImage, ivPlay;
    TextView tvTitle, tvTime;
    ProgressBar pbTime;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play);

        // 뷰 초기화
        ivImage = findViewById(R.id.ivImage);
        ivPlay = findViewById(R.id.ivPlay);
        tvTitle = findViewById(R.id.tvTitle);
        tvTime = findViewById(R.id.tvTime);
        pbTime = findViewById(R.id.pbTime);

        // 인텐트에서 뮤직 아이템 받기
        MusicItem item = getIntent().getParcelableExtra("MUSIC_ITEM");
        position = getIntent().getIntExtra("INDEX", 0);
        updateMusicInfo(item);

        // 바운드 서비스 연결 후 자동으로 음악 재생
        Intent serviceIntent = new Intent(this, MusicService.class);
        mConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                mBinder = IMusicService.Stub.asInterface(service);
                try {
                    mBinder.Play(position);
                    isPlaying = true;
                    ivPlay.setImageResource(R.drawable.ic_baseline_pause_24);

                    // 진행도 스레드 생성 및 실행
                    seekThread = new Thread(PlayActivity.this::seekAndUpdateUIThread);
                    seekThread.start();
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
                updateMusicInfo(mBinder.Prev());
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
                updateMusicInfo(mBinder.Next());
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
        if (seekThread != null && seekThread.isAlive())
            seekThread.interrupt();
        super.onDestroy();
    }

    // 앨범의 이미지, 곡이름 등을 통해 UI 업데이트
    void updateMusicInfo(MusicItem item) {
        duration = item.getDuration();

        ivImage.setImageBitmap(item.getImage(this));
        tvTitle.setText(item.getTitle());
        tvTime.setText(String.format(Locale.KOREA, "00:00 / %s",
                MusicItem.convertDurationToString(duration)));
        pbTime.setMax((int)duration);
    }

    void seekAndUpdateUIThread() {
        try {
            while (true) {
                int[] info = mBinder.getCurrentInfo();

                runOnUiThread(() -> {
                    // 새로운 노래가 재생되었을 경우
                    if (position != info[0]) {
                        position = info[0];
                        try {
                            updateMusicInfo(mBinder.getMusicItem(position));
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }

                    // 진행도 변경
                    tvTime.setText(
                            String.format(Locale.KOREA, "%s / %s",
                                    MusicItem.convertDurationToString(info[1]),
                                    MusicItem.convertDurationToString(duration)));
                    pbTime.setProgress(info[1], true);

                    // 재생중 판단하여 아이콘 변경
                    if (info[2] == 1 && !isPlaying) {
                        isPlaying = true;
                        ivPlay.setImageResource(R.drawable.ic_baseline_pause_24);
                    }
                    else if (info[2] == 0 && isPlaying) {
                        isPlaying = false;
                        ivPlay.setImageResource(R.drawable.ic_baseline_play_arrow_24);
                    }
                });

                Thread.sleep(100);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}