package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;

public class ImplicitActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_implicit);

        findViewById(R.id.btnMain).setOnClickListener(view ->
                startActivity(new Intent(Intent.ACTION_MAIN))
        );

        findViewById(R.id.btnBrowser).setOnClickListener(view ->{
            Intent intent = new Intent(Intent.ACTION_MAIN);
            intent.addCategory(Intent.CATEGORY_BROWSABLE);
            startActivity(intent);
        });

        findViewById(R.id.btnCalculator).setOnClickListener(view ->{
            Intent intent = new Intent(Intent.ACTION_MAIN);
            intent.addCategory(Intent.CATEGORY_APP_CALCULATOR);
            startActivity(intent);
        });

        findViewById(R.id.btnAlarm).setOnClickListener(view -> {
//            Intent intent = new Intent(Intent.ACTION_VIEW);
//            intent.addCategory(Intent.CATEGORY_APP_MUSIC);
//            intent.setDataAndType(Uri.parse("file:///sdcard/Music/으나알람.mp3"),"audio/*");
//            startActivity(intent);
            Intent intent = Intent.makeMainSelectorActivity(Intent.ACTION_MAIN, Intent.CATEGORY_APP_MUSIC);
            intent.addFlags((Intent.FLAG_ACTIVITY_NEW_TASK));
            intent.setDataAndType(Uri.parse("file:///sdcard/Music/으나알람.mp3"),"audio/*");
            startActivity(intent);;
        });
    }
}