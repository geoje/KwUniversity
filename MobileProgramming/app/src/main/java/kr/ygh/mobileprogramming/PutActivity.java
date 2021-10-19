package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class PutActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_put);

        if (getIntent().hasExtra("DATA"))
            ((TextView)findViewById(R.id.tvPut)).setText(getIntent().getStringExtra("DATA"));
    }
}