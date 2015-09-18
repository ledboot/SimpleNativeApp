package com.wawov.nativeapp.activity;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import com.wawov.nativeapp.R;
import com.wawov.nativeapp.model.Container;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity{

    public static String TAG = MainActivity.class.getSimpleName();

    static {
        System.loadLibrary("hello");
    }

    TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        /*tv = (TextView) findViewById(R.id.id_tv);
        tv.setText(stringFromJni());
        StringBuilder builder = new StringBuilder();
        int [] arr = new int[5];
        arrayFromJni(arr);
        for(int i: arr){
            builder.append(i+",");
        }
        Log.d(TAG,"arr from jni:"+builder.toString());*/
        ArrayList<Container> list = new ArrayList<>();
        /*Container t1 = new Container(1,"gg",false);
        Container t2 = new Container(2,"3e",false);
        Container t3 = new Container(3,"ssf",true);

        list.add(t1);
        list.add(t2);
        list.add(t3);

        jniContainer(list);*/
        jniCreateArray(list);
        Log.d(TAG,"list size "+list.size());
    }

    public native  String stringFromJni();

    public native  void arrayFromJni(int[] arr);

    public native void jniContainer(ArrayList<Container> list);

    public native void jniCreateArray(ArrayList<Container> list);

}