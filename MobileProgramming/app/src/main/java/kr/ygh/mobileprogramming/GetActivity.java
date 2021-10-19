package kr.ygh.mobileprogramming;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.EditText;

public class GetActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_get);

        findViewById(R.id.btnGetFinish).setOnClickListener(view -> {
            String data = ((EditText)findViewById(R.id.etGet)).getText().toString();
            Intent intent = new Intent();
            intent.putExtra(Intent.EXTRA_TEXT, data);
            setResult(RESULT_OK, intent);
            finish();
        });
    }
}