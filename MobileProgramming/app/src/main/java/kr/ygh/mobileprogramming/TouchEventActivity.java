package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.SystemClock;
import android.view.MotionEvent;
import android.widget.TextView;
import android.widget.Toast;

public class TouchEventActivity extends AppCompatActivity {
    TextView tvX, tvY;
    long mExitModeTime = 0L;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_touch_event);

        tvX = findViewById(R.id.tvX);
        tvY = findViewById(R.id.tvY);
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        tvX.setText(Float.toString(event.getX()));
        tvY.setText(Float.toString(event.getY()));
        return super.onTouchEvent(event);
    }

    @Override
    public void onBackPressed() {
        if (mExitModeTime !=0 && SystemClock.uptimeMillis() - mExitModeTime < 3000)
            finish();
        else {
            Toast.makeText(this, "이전 키를 한번 더 누르면 종료됩니다.", Toast.LENGTH_SHORT).show();
            mExitModeTime = SystemClock.uptimeMillis();
        }
    }
}