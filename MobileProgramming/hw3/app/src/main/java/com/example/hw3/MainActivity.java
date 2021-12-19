package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.Intent;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.IBinder;
import android.os.ParcelFileDescriptor;
import android.os.RemoteException;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.ListView;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class MainActivity extends AppCompatActivity {
    private IMusicService mBinder;
    private ServiceConnection mConnection;

    ListView lvMain;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 저장소 엑세스 권한 요청
        if (checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED)
            requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 1);

        // 커스텀 리스트 뷰
        lvMain = findViewById(R.id.lvMain);
        lvMain.setOnItemClickListener((parent, view, position, id) -> {
            MusicItem item = (MusicItem)((ListViewAdapter)parent.getAdapter()).getItem(position);

            Intent intent = new Intent(MainActivity.this, PlayActivity.class);
            intent.putExtra("MUSIC_ITEM", item);
            intent.putExtra("INDEX", position);
            startActivity(intent);
        });

        // 뮤직 서비스 연결
        mConnection = new ServiceConnection() {

            // 서비스 연결시 뮤직 정보들을 리스트뷰에 추가
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                mBinder = IMusicService.Stub.asInterface(service);
                InitUI();
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {

            }
        };
        Intent serviceIntent = new Intent(this, MusicService.class);
        bindService(serviceIntent, mConnection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onDestroy() {
        unbindService(mConnection);
        super.onDestroy();
    }

    void InitUI() {
        // 서비스에서 음악 리스트가 로드될 때 까지 0.1 ~ 0.2초 무한 랜덤 대기
        new Thread(() -> {
            List<MusicItem> items = null;
            Random rand = new Random();

            try {
                while ((items = mBinder.getMusicItems()) == null) {
                    Thread.sleep(rand.nextInt(100) + 100);
                }
            }
            catch (Exception e) {
                e.printStackTrace();
            }

            // 끝나면 UI 업데이트
            List<MusicItem> finalItems = items;
            runOnUiThread(() -> {
                // 리스트 뷰 보이기
                lvMain.setVisibility(View.VISIBLE);

                // 리스트 뷰 데이터 추가
                ListViewAdapter adapter = new ListViewAdapter();
                finalItems.forEach(adapter::addItem);
                lvMain.setAdapter(adapter);

                // 써큘러 프로그래스 바 가리기
                findViewById(R.id.pbLoading).setVisibility(View.GONE);
            });
        }).start();
    }
}