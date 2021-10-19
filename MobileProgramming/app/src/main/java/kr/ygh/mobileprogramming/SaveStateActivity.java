package kr.ygh.mobileprogramming;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.EditText;

public class SaveStateActivity extends AppCompatActivity {
    EditText etSS;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_save_state);
        etSS = findViewById(R.id.etSS);
        if (savedInstanceState != null)
            etSS.setText(savedInstanceState.getString("BACKUP_STR"));
    }

    @Override
    protected void onSaveInstanceState(@NonNull Bundle outState) {
        outState.putString("BACKUP_STR", etSS.getText().toString());
        super.onSaveInstanceState(outState);
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle savedInstanceState) {
        if (savedInstanceState != null)
            etSS.setText(savedInstanceState.getString("BACKUP_STR"));
        super.onRestoreInstanceState(savedInstanceState);
    }
}