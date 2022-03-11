package com.example.hw2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;

import java.math.BigDecimal;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class MyCalculator extends AppCompatActivity {
    String expression = "";
    TextView tvExpr, tvResult;
    HashMap<Character, Button> btns = new HashMap<>();

    Queue<Character> q;
    Stack<Double> operands;
    Stack<Character> operators;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_calculator);

        // 결과 텍스트
        tvExpr =  (TextView) findViewById(R.id.tvExpr);
        tvResult =  (TextView) findViewById(R.id.tvResult);

        // 계산 버튼들
        btns.put('1', (Button) findViewById(R.id.btn1));
        btns.put('2', (Button) findViewById(R.id.btn2));
        btns.put('3', (Button) findViewById(R.id.btn3));
        btns.put('4', (Button) findViewById(R.id.btn4));
        btns.put('5', (Button) findViewById(R.id.btn5));
        btns.put('6', (Button) findViewById(R.id.btn6));
        btns.put('7', (Button) findViewById(R.id.btn7));
        btns.put('8', (Button) findViewById(R.id.btn8));
        btns.put('9', (Button) findViewById(R.id.btn9));
        btns.put('0', (Button) findViewById(R.id.btn0));

        btns.put('+', (Button) findViewById(R.id.btnAdd));
        btns.put('-', (Button) findViewById(R.id.btnSub));
        btns.put('*', (Button) findViewById(R.id.btnMul));
        btns.put('/', (Button) findViewById(R.id.btnDiv));
        btns.put('.', (Button) findViewById(R.id.btnDot));
        btns.put('=', (Button) findViewById(R.id.btnRes));

        btns.forEach((c, btn) -> btn.setOnClickListener(v -> {
            if (c == '=') tvResult.setText(calculateByJS());
            else tvExpr.setText(expression += c);
        }));

        // 웹 버튼
        findViewById(R.id.btnWeb).setOnClickListener(v ->
            startActivity(new Intent(MyCalculator.this, MyWebBrowser.class))
        );

        // 공유 인텐트 받기
        initIntent();
    }

    void initIntent() {
        Intent intent = getIntent();

        if (!intent.getAction().equals(Intent.ACTION_SEND) ||
                !intent.getType().equals("text/plain"))
            return;

        tvExpr.setText(expression = intent.getStringExtra(Intent.EXTRA_TEXT));
        tvResult.setText(calculateByJS());
    }

    double popNumber() {
        String token = "";

        while (!q.isEmpty()) {
            char c = q.peek();

            if (c >= '0' && c <= '9' || c == '.')
                token += c;
            else break;

            q.remove();
        }

        return Double.parseDouble(token);
    }
    boolean calcByStack() {
        if (operands.size() < 2 || operators.isEmpty())
            return false;
        
        double right = operands.pop();
        double left = operands.pop();
        char op = operators.pop();

        if (op == '+') operands.push(left + right);
        else if (op == '-') operands.push(left - right);
        else if (op == '*') operands.push(left * right);
        else if (op == '/') operands.push(left / right);
        return true;
    }
    String calculateByStack() {
        // 자료구조 초기화
        q = new LinkedList<>();
        operands = new Stack<>();
        operators = new Stack<>();

        // 계산식 큐에다 집어넣기
        for (char c : expression.toCharArray())
            q.add(c);

        while (!q.isEmpty()) {
            char c = q.peek();

            if (c == 'x' || c == 'X') {
                operators.push('*');
                q.remove();
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/') {
                operators.push(c);
                q.remove();
            }
            else {
                operands.push(popNumber());

                // 연산자가 있을 경우 곱셈, 나눗셈 먼저 게산
                if (!operators.isEmpty()) {
                    c = operators.peek();
                    if (c == '*' || c == '/')
                        calcByStack();
                }
            }
        }

        // 남은 연산 (덧셈, 나눗셈) 계산
        while (calcByStack()) ;
        return new BigDecimal(operands.peek()).toString();
    }
    String calculateByJS() {
        javax.script.ScriptEngine engine = new javax.script.ScriptEngineManager().getEngineByName("rhino");
        String result;
        try {
            result = engine.eval(expression.replaceAll("[xX]", "*")).toString();
        }
        catch(javax.script.ScriptException e) {
            result = "Expression Error";
        }
        return result;
    }
}