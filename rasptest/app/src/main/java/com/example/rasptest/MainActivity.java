package com.example.rasptest;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    private Handler mHandler;
    Socket socket;
    private String ip ="127.0.0.1";
    private int port = 8080;
    EditText ipText;
    EditText portText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHandler = new Handler();
        ipText = (EditText) findViewById(R.id.iptext);
        portText = (EditText) findViewById(R.id.porttext);
        Button changeBtn = (Button) findViewById(R.id.change);

        changeBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (ipText.getText().toString() != null) {
                        ConnectThread th = new ConnectThread();
                        th.start();
                        Intent intent = new Intent(MainActivity.this, SubActivity.class);
                        startActivity(intent);
                }
            }
        });
    }

    class ConnectThread extends Thread{
        public void run(){
            try {
                InetAddress serverAddr = InetAddress.getByName(ip);
                socket = new Socket(serverAddr, port);
                String sndIP = ipText.getText().toString();
                Log.d("=============", sndIP);
                PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())),true);
                out.println(sndIP);
                //데이터 수신
                BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String read = input.readLine();
                socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}