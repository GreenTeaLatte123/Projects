package com.example.app;

import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.bumptech.glide.Glide;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.firebase.storage.FirebaseStorage;
import com.google.firebase.storage.StorageReference;

public class CtrlActivity extends AppCompatActivity {

    private static final String TAG = "CtrlActivity";
    private ImageView imageView;
    private DatabaseReference databaseReference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ctrl);

        imageView = findViewById(R.id.image);

        databaseReference = FirebaseDatabase.getInstance().getReference("image");

        databaseReference.child("download_url").addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                // 이미지 URL을 가져옴
                String imageUrl = dataSnapshot.getValue(String.class);

                // Glide 또는 Picasso와 같은 라이브러리를 사용하여 이미지 로드
                Glide.with(CtrlActivity.this).load(imageUrl).into(imageView);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {
                // 데이터 가져오기를 실패했을 때 호출됨
                Log.e(TAG, "Failed to read image URL.", databaseError.toException());
            }
        });
    }
}
