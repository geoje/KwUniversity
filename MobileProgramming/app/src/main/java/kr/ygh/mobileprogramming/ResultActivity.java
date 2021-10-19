package kr.ygh.mobileprogramming;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.EditText;
import android.widget.TextView;

public class ResultActivity extends AppCompatActivity {
    static int REQUEST_DATA = 0x00001;
    EditText etData;
    TextView tvData;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_result);
        etData = findViewById(R.id.etData);
        tvData = findViewById(R.id.tvData);

        findViewById(R.id.btnSend).setOnClickListener(view -> {
            Intent intent = new Intent(this, PutActivity.class);
            intent.putExtra("DATA", etData.getText().toString());
            startActivity(intent);
        });
        findViewById(R.id.btnReceive).setOnClickListener(view -> {
            Intent intent = new Intent(this, GetActivity.class);
//            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            startActivityForResult(intent, REQUEST_DATA);
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_DATA && resultCode == RESULT_OK)
            tvData.setText(data != null ? data.getStringExtra(Intent.EXTRA_TEXT) : null);
    }
}