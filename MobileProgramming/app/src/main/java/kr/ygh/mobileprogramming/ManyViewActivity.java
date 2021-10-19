package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class ManyViewActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_many_view);

        ((TextView)findViewById(R.id.tvHelloWorld)).setText("Hello World!");
        findViewById(R.id.tvMarquee).setSelected(true);
    }
}