package com.example.hw3;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.database.Cursor;
import android.media.MediaPlayer;
import android.media.MediaScannerConnection;
import android.os.Build;
import android.os.Environment;
import android.os.IBinder;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MusicService extends Service {
    public static String MAIN_ACTION = "com.example.hw3.action.main";
    public static String PLAY_ACTION = "com.example.hw3.action.play";
    public static String PREV_ACTION = "com.example.hw3.action.prev";
    public static String NEXT_ACTION = "com.example.hw3.action.next";

    public static String CHANNEL_ID = "channel_music";
    public static String CHANNEL_NAME = "kwmp_channel";
    public static int NOTIFICATION_ID = 1213;

    boolean loaded = false;
    ArrayList<MusicItem> items = new ArrayList<>();
    int position;
    MediaPlayer player;

    NotificationCompat.Builder notiBuilder;

    IMusicService.Stub mBinder = new IMusicService.Stub() {
        @Override
        public MusicItem Play(int index, int seekPos) throws RemoteException {
            if (player != null) player.release();
            position = index;
            MusicItem item = items.get(position);

            // 미디어 플레이어를 새로 만들고 음악 재생
            try {
                player = new MediaPlayer();
                player.setDataSource(item.getFilename());
                player.setOnPreparedListener(mp -> {
                    mp.seekTo(seekPos);
                    mp.start();
                    Notify(item);
                });
                player.prepareAsync();
                player.setOnCompletionListener(mp -> {
                    try {
                        Next();
                    } catch (RemoteException e) {
                        e.printStackTrace();
                    }
                });
            } catch (IOException e) {
                e.printStackTrace();
            }

            return item;
        }

        @Override
        public void Pause() throws RemoteException {
            player.pause();
        }
        @Override
        public void Resume() throws RemoteException {
            player.start();
        }
        @Override
        public MusicItem Next() throws RemoteException {
            position = ++position % items.size();
            Play(position, 0);
            return items.get(position);
        }
        @Override
        public MusicItem Prev() throws RemoteException {
            if (--position <= 0) position = items.size() - 1;
            Play(position, 0);
            return items.get(position);
        }

        @Override
        public List<MusicItem> getMusicItems() throws RemoteException {
            return loaded ? items : null;
        }

        @Override
        public MusicItem getMusicItem(int index) throws RemoteException {
            return items.get(index);
        }

        @Override
        public boolean isPlaying() throws RemoteException {
            return player.isPlaying();
        }

        @Override
        public int[] getCurrentInfo() throws RemoteException {
            int info[] = new int[] { position, 0, 1 };

            try {
                info[1] = player.getCurrentPosition();
                info[2] = player.isPlaying() ? 1 : 0;
            }
            catch (Exception e) { }

            // 현재 노래 인덱스, 현재 진행 위치, 재생 중 여부
            return info;
        }
    };

    // 미디어 스캐너에 갱신 요청 후 미디어 스토어의 음악 파일 로드
    @Override
    public void onCreate() {
        Log.i("MusicService.onCreate()", "");
        // 미디어 스캐너로 음악 리스트 로드
        MediaScannerConnection.scanFile(
                getApplicationContext(),
                new String[] {Environment.getExternalStorageDirectory().getAbsolutePath()},
                null,
                (path, uri) -> {
                    // 쿼리 실행하여 커서 가져오기
                    Cursor cursor = getContentResolver().query(
                            MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                            new String[] {
                                    MediaStore.Audio.Media.TITLE,
                                    MediaStore.Audio.Media.DATA,
                                    MediaStore.Audio.Media.ALBUM_ID,
                                    MediaStore.Audio.Media.DURATION
                            }, null, null, null);

                    // 순회하여 리스트뷰에 추가
                    if (cursor.moveToFirst()) {
                        do {
                            // 커서에서 데이터 추출
                            String title = cursor.getString(0);
                            String filename = cursor.getString(1);
                            long albumId = cursor.getLong(2);
                            long duration = cursor.getLong(3);

                            // 확장자 'mp3'만 추출
                            if (!filename.endsWith(".mp3")) continue;

                            // 리스트뷰에 추가
                            items.add(new MusicItem(title, filename, albumId, duration));
                        } while (cursor.moveToNext());
                        loaded = true;
                    }
                    cursor.close();
                });
        super.onCreate();
    }

    @Override
    public void onDestroy() {
        Log.i("MusicService.onDestroy()", "");
        if (player != null)
            player.release();
        super.onDestroy();
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        try {
            if (intent.getAction().equals(PLAY_ACTION)) {
                if (mBinder.isPlaying()) {
                    mBinder.Pause();
                }
                else
                    mBinder.Resume();

                Notify(items.get(position));
            }
            else if (intent.getAction().equals(PREV_ACTION)) {
                mBinder.Prev();
            }
            else if (intent.getAction().equals(NEXT_ACTION)) {
                mBinder.Next();
            }
        } catch (RemoteException e) {
            e.printStackTrace();
        }

        return START_STICKY;
    }

    public void Notify(MusicItem item) {
        // API 26이상 알림 채널 설정
        NotificationManager nManager = (NotificationManager)getSystemService(NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= 26) {
            NotificationChannel channel = new NotificationChannel(
                    CHANNEL_ID, CHANNEL_NAME,
                    NotificationManager.IMPORTANCE_DEFAULT
            );
            nManager.createNotificationChannel(channel);
        }

        // 알림창을 클릭했을 때
        Intent mainIntent = new Intent(getApplicationContext(), PlayActivity.class);
        mainIntent.setAction(MAIN_ACTION);
        mainIntent.putExtra("MUSIC_ITEM", items.get(position));
        mainIntent.putExtra("INDEX", position);
        mainIntent.putExtra("SEEK_POS", player.getCurrentPosition());
        mainIntent.putExtra("IS_PLAYING", player.isPlaying());
        PendingIntent pMainIntent = PendingIntent.getActivity(MusicService.this, 0, mainIntent,
                PendingIntent.FLAG_CANCEL_CURRENT);

        // 이전 버튼
        Intent prevIntent = new Intent(MusicService.this, MusicService.class);
        prevIntent.setAction(PREV_ACTION);
        PendingIntent pPrevIntent = PendingIntent.getService(MusicService.this, 0, prevIntent, 0);

        // 플레이 버튼
        Intent playIntent = new Intent(MusicService.this, MusicService.class);
        playIntent.setAction(PLAY_ACTION);
        PendingIntent pPlayIntent = PendingIntent.getService(MusicService.this, 0, playIntent, 0);

        // 다음 버튼
        Intent nextIntent = new Intent(MusicService.this, MusicService.class);
        nextIntent.setAction(NEXT_ACTION);
        PendingIntent pNextIntent = PendingIntent.getService(MusicService.this, 0, nextIntent, 0);

        // 알림창 세팅
        notiBuilder = new NotificationCompat.Builder(MusicService.this, CHANNEL_ID)
                .setSmallIcon(player.isPlaying() ? R.drawable.ic_baseline_play_arrow_24 : R.drawable.ic_baseline_pause_24)
                .setLargeIcon(item.getImage(MusicService.this))
                .setContentTitle("광운 모프 플레이어")
                .setContentText(item.getTitle())
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setContentIntent(pMainIntent)
                .addAction(R.drawable.ic_baseline_skip_previous_24, "이전", pPrevIntent)
                .addAction(
                        player.isPlaying() ? R.drawable.ic_baseline_pause_24 : R.drawable.ic_baseline_play_arrow_24,
                        player.isPlaying() ? "일시정지" :"재생", pPlayIntent)
                .addAction(R.drawable.ic_baseline_skip_next_24, "다음", pNextIntent);

        // 알림 시작!!!
        startForeground(NOTIFICATION_ID, notiBuilder.build());
    }
}
