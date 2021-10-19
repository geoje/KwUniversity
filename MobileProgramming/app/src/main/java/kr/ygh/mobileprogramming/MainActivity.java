package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.strictmode.ImplicitDirectBootViolation;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btnFrameLayout).setOnClickListener(view ->
                startActivity(new Intent(this, FrameLayoutActivity.class)));
        findViewById(R.id.btnRelativeLayout).setOnClickListener(view ->
                startActivity(new Intent(this, RelativeLayoutActivity.class)));
        findViewById(R.id.btnTableLayout).setOnClickListener(view ->
                startActivity(new Intent(this, TableLayoutActivity.class)));
        findViewById(R.id.btnTouchEvent).setOnClickListener(view ->
                startActivity(new Intent(this, TouchEventActivity.class)));
        findViewById(R.id.btnImplicitIntent).setOnClickListener(view ->
                startActivity(new Intent(this, ImplicitActivity.class)));
        findViewById(R.id.btnImplicitComponent).setOnClickListener(view ->
                startActivity(new Intent(this, ImplicitComponentActivity.class)));
        findViewById(R.id.btnSaveState).setOnClickListener(view ->
                startActivity(new Intent(this, SaveStateActivity.class)));
        findViewById(R.id.btnResult).setOnClickListener(view ->
                startActivity(new Intent(this, ResultActivity.class)));
    }
}