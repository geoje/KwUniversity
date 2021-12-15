package com.example.hw3;

import android.app.Service;
import android.content.Intent;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.Nullable;

public class MusicService extends Service {
    MediaPlayer player;

    IMusicService.Stub mBinder = new IMusicService.Stub() {
        @Override
        public void Start(String filename) throws RemoteException {
            if (player != null) player.release();

            player = MediaPlayer.create(MusicService.this, Uri.parse(filename));
            player.setOnPreparedListener(mp -> {
                mp.start();
                Log.i("start", "start");
            });
            player.prepareAsync();

            Log.i("prepareAsync", "prepareAsync");
        }

        @Override
        public void Pause() throws RemoteException {
            player.pause();
        }

        @Override
        public void Resume() throws RemoteException {
            player.start();
        }
    };

    @Override
    public void onDestroy() {
        if (player != null)
            player.release();
        super.onDestroy();
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return super.onStartCommand(intent, flags, startId);
    }
}
