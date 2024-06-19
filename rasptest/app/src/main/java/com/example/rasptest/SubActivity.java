package com.example.rasptest;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class SubActivity extends AppCompatActivity {

    private String ip = "127.0.0.1";
    private int port = 8080;
    private Handler mHandler;
    Socket socket;

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
        setContentView(R.layout.activity_sub);

        mHandler = new Handler();

        Button chadan = (Button) findViewById(R.id.chadan);

        chadan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonThread bt=new buttonThread("chadan");
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

    class msgUpdate implements Runnable {
        private String msg;
        public msgUpdate(String str) {
            this.msg = str;
        }
        public void run() {
            Toast myToast = Toast.makeText(getApplicationContext(), "연결 중입니다.", Toast.LENGTH_SHORT);
        }
    };
}