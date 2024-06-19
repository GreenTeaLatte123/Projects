package com.example.test;

import androidx.appcompat.app.AppCompatActivity;

import android.media.Image;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.webkit.DownloadListener;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    private String TAG = MainActivity.class.getSimpleName();
    private WebView webView = null;
    private Button ledButton;
    private Handler mHandler;
    Socket socket;
    private String ip = "192.168.137.97"; // IP 주소
    private int port = 8080; // PORT번호
    EditText inputText;
    TextView logText;

    @Override
    protected void onStop() {
        super.onStop();
        try {
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        webView = (WebView) findViewById(R.id.webview);

        webView.setWebViewClient(new WebViewClient());
        webView.setWebChromeClient(new WebChromeClient());
        webView.getSettings().setLoadWithOverviewMode(true);
        webView.getSettings().setUseWideViewPort(true);
        webView.getSettings().setSupportZoom(false);
        webView.getSettings().setBuiltInZoomControls(false);
        webView.getSettings().setDomStorageEnabled(true);
        webView.loadUrl("http://192.168.137.124:8081/?action=stream");

        mHandler = new Handler();
        inputText = (EditText) findViewById(R.id.inputEditText);
        Button sendMsgButton = (Button) findViewById(R.id.sendMsgButton);
        ImageButton turnOnLightButton = (ImageButton)findViewById(R.id.turnOnLightButton);
        ImageButton turnOffLightButton = (ImageButton)findViewById(R.id.turnOffLightButton);
        ImageButton leftButton = (ImageButton)findViewById(R.id.LeftBtn);
        ImageButton centerButton = (ImageButton)findViewById(R.id.CenterBtn);
        ImageButton rightButton = (ImageButton)findViewById(R.id.RightBtn);
        ImageButton goButton = (ImageButton)findViewById(R.id.GoBtn);
        ImageButton stopButton = (ImageButton)findViewById(R.id.StopBtn);
        ImageButton backButton = (ImageButton)findViewById(R.id.BackBtn);

        logText = (TextView)findViewById(R.id.logTextView);

        sendMsgButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (inputText.getText().toString() != null || !inputText.getText().toString().equals("")) {
                    buttonThread th =new buttonThread(inputText.getText().toString());
                    th.start();
                }
            }
        });

        turnOnLightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("turnOn");
                bt.start();
            }
        });

        turnOffLightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("turnOff");
                bt.start();
            }
        });

        leftButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("LEFT");
                bt.start();
            }
        });

        centerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("CENTER");
                bt.start();
            }
        });

        rightButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("RIGHT");
                bt.start();
            }
        });

        goButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("GO");
                bt.start();
            }
        });

        backButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("BACK");
                bt.start();
            }
        });

        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("STOP");
                bt.start();
            }
        });
    }

    class buttonThread extends Thread{
        String msg;
        public buttonThread(String msg){
            this.msg=msg;
        }


        public void run(){
            try{
                //소켓 생성
                InetAddress serverAddr = InetAddress.getByName(ip);
                socket =  new Socket(serverAddr,port);
                //입력 메시지
                String sndMsg = msg;
                Log.d("=============", sndMsg);
                //데이터 전송
                PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())),true);
                out.println(sndMsg);
                //데이터 수신
                BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String read = input.readLine();
                //화면 출력
                mHandler.post(new msgUpdate(read));
                Log.d("=============", read);
                socket.close();
            }catch(Exception e){
                e.printStackTrace();
            }
        }
    }
    // 받은 메시지 출력
    class msgUpdate implements Runnable {
        private String msg;
        public msgUpdate(String str) {
            this.msg = str;
        }
        public void run() {
            logText.setText(logText.getText().toString() + msg + "\n");
        }
    };



}