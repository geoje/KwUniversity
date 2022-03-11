package com.example.hw2;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.inputmethod.InputMethodManager;
import android.webkit.JavascriptInterface;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.EditText;

public class MyWebBrowser extends AppCompatActivity {
    WebView wv;
    EditText etUrl;
    WebSettings wvSetting;
    InputMethodManager imm;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_web_browser);

        // 주소창 및 키보드
        etUrl = (EditText) findViewById(R.id.etUrl);
        imm = (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);

        // 웹 뷰
        wv = (WebView) findViewById(R.id.wv);
        WebViewClient mWebViewClient = new WebViewClient() {
            @Override
            public void onPageFinished(WebView view, String url) {
                view.loadUrl("javascript:window.android.onUrlChange(window.location.href);");
            };
        }; // URL 변경 감지
        wv.setWebViewClient(mWebViewClient);
        wv.addJavascriptInterface(new MyJavaScriptInterface(), "android"); // URL 변경 감지
        wvSetting = wv.getSettings();
        wvSetting.setJavaScriptEnabled(true);
        wvSetting.setSupportMultipleWindows(false);
        wvSetting.setJavaScriptCanOpenWindowsAutomatically(false);
        wvSetting.setLoadWithOverviewMode(true);
        wvSetting.setUseWideViewPort(true);
        wvSetting.setSupportZoom(false);
        wvSetting.setBuiltInZoomControls(false);
        wvSetting.setCacheMode(WebSettings.LOAD_NO_CACHE);
        wvSetting.setDomStorageEnabled(true);
        wv.loadUrl(etUrl.getText().toString());

        // 주소창 이벤트
        etUrl.setOnKeyListener((v, keyCode, event) -> {
            if (event.getAction() == KeyEvent.ACTION_DOWN
                    && keyCode == KeyEvent.KEYCODE_ENTER) {
                wv.loadUrl(etUrl.getText().toString());
                imm.hideSoftInputFromWindow(etUrl.getWindowToken(), 0);
                return true;
            }
            return false;
        });

        // 페이지 전환 버튼
        findViewById(R.id.btnPrev).setOnClickListener(v -> {
            if (wv.canGoBack()) wv.goBack();
        });
        findViewById(R.id.btnNext).setOnClickListener(v -> {
            if (wv.canGoForward()) wv.goForward();
        });

        // 계산기 버튼
        findViewById(R.id.btnCalc).setOnClickListener(v -> finish());

        // 공유 인텐트 받기
        initIntent();
    }

    void initIntent() {
        Intent intent = getIntent();

        if (intent.getAction() == null || !intent.getAction().equals(Intent.ACTION_SEND))
            return;
        if (intent.getType() == null || !intent.getType().equals("text/plain"))
            return;

        String url = intent.getStringExtra(Intent.EXTRA_TEXT);
        etUrl.setText(url);
        wv.loadUrl(url);
    }

    class MyJavaScriptInterface {
        @JavascriptInterface
        public void onUrlChange(String url) {
            etUrl.setText(url);
        }
    }
}