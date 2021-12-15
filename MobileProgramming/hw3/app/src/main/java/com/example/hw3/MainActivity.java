package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.util.Log;
import android.widget.ListView;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 커스텀 리스트 뷰
        ListView lvMain = findViewById(R.id.lvMain);
        lvMain.setOnItemClickListener((parent, view, position, id) -> {
            Intent intent = new Intent(MainActivity.this, PlayActivity.class);
            intent.putParcelableArrayListExtra("MUSIC_ITEMS", ((ListViewAdapter)parent.getAdapter()).getAllItems());
            intent.putExtra("POSITION", position);
            startActivity(intent);
        });

        // 저장소 엑세스 권한 요청
        if (checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE)
                != PackageManager.PERMISSION_GRANTED)
            requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 1);

        // 미디어 스캐너
        MediaScannerConnection.scanFile(
                getApplicationContext(),
                new String[] {Environment.getExternalStorageDirectory().getAbsolutePath()},
                null,
                (path, uri) -> {
                    // 리스트뷰에 아이템들 넣기
                    ArrayList<MusicItem> items = getMusicItemListFromMediaStore();
                    MainActivity.this.runOnUiThread(() -> {
                        ListViewAdapter adapter = new ListViewAdapter();
                        items.forEach(adapter::addItem);
                        lvMain.setAdapter(adapter);
                    });
                });
    }

    ArrayList<MusicItem> getMusicItemListFromMediaStore() {
        ArrayList<MusicItem> items = new ArrayList<>();

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
        }
        cursor.close();

        return items;
    }
}