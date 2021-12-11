package com.example.kwmp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.widget.TextView;

import java.util.Locale;
import java.util.Random;

public class ThreadThirdActivity extends AppCompatActivity {
    TextView tvDownload, tvCount;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_thread_third);
        setTitle(getIntent().getStringExtra("title"));

        // 다운로드 TaskAsync
        tvDownload = findViewById(R.id.tvDownload);
        DownloadTask task = new DownloadTask();
        task.execute("FileUrl1", "FileUrl2", "FileUrl3", "FileUrl4", "FileUrl5",
                "FileUrl6", "FileUrl7", "FileUrl8", "FileUrl9", "FileUrl10");
        findViewById(R.id.btnCancelCount).setOnClickListener(o -> {
            if (task != null && task.getStatus() != AsyncTask.Status.FINISHED)
                /** doInBackground 가 중단되는 것이 아님.
                 * 도중 publishProgress 함수를 호출해도 onProgressUpdate 가 실행되지 않을 뿐임. */
                task.cancel(true);
        });

        // 카운팅 CountDownTimer
        tvCount = findViewById(R.id.tvCount);
        MyCountDownTimer timer = new MyCountDownTimer(60000, 10);
        findViewById(R.id.btnStartCount).setOnClickListener(o -> timer.start());
        findViewById(R.id.btnCancelCount).setOnClickListener(o -> timer.cancel());
    }

    class DownloadTask extends AsyncTask<String, Integer, Boolean> {
        @Override
        protected void onPreExecute() {
            tvDownload.setText("다운로드가 시작되었습니다!");
            super.onPreExecute();
        }

        @Override
        protected Boolean doInBackground(String... strings) {
            Random r = new Random();
            for (int i = 1; i <= 10; i++)
            {
                try { Thread.sleep(r.nextInt(1000) + 400); }
                catch (Exception e) {}
                publishProgress(i, 10);
            }
            /* 여기서 파일의 무결성 검사를 한 뒤 정상 유무에 따라 리턴하여
             * onPostExecute 로 넘겨주면 된다.
             */
            return true;
        }

        @Override
        protected void onProgressUpdate(Integer... values) {
            tvDownload.setText(String.format(Locale.KOREA, "다운로드 상태: %d / %d", values[0], values[1]));
            super.onProgressUpdate(values);
        }

        @Override
        protected void onCancelled() {
            tvDownload.setText("다운로드가 취소되었습니다!");
            super.onCancelled();
        }

        @Override
        protected void onPostExecute(Boolean aBoolean) {
            tvDownload.setText(aBoolean ? "다운로드가 성공적으로 끝났습니다!" : "다운로드가 실패하였습니다.");
            super.onPostExecute(aBoolean);
        }
    }
    class MyCountDownTimer extends CountDownTimer {
        /**
         * @param millisInFuture    The number of millis in the future from the call
         *                          to {@link #start()} until the countdown is done and {@link #onFinish()}
         *                          is called.
         * @param countDownInterval The interval along the way to receive
         *                          {@link #onTick(long)} callbacks.
         */
        public MyCountDownTimer(long millisInFuture, long countDownInterval) {
            super(millisInFuture, countDownInterval);
        }

        @Override
        public void onTick(long millisUntilFinished) {
            tvCount.setText(String.format(Locale.KOREA, "%.2f초", millisUntilFinished / 1000.0));
        }

        @Override
        public void onFinish() {
            tvCount.setText("카운트 다운 종료");
        }
    }
}