package com.example.kwmp;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.Toast;

import androidx.annotation.Nullable;

public class CountService extends Service {
    Thread countThread;
    int count;

    ICountService.Stub mBinder = new ICountService.Stub() {
        @Override
        public int getCurCountNumber() throws RemoteException {
            return 0;
        }

        @Override
        public void basicTypes(int anInt, long aLong, boolean aBoolean, float aFloat, double aDouble, String aString) throws RemoteException {

        }
    };

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        Log.i("kwmp", "onCreate()");
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        super.onStartCommand(intent, flags, startId);
        Log.i("kwmp", "onStartCommand()");

        if (countThread == null) {
            countThread = new Thread(() -> {
                while (true) {
                    count++;
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                        break;
                    }
                }
            });
            countThread.start();
        }
        return START_STICKY;
    }

    @Override
    public void onDestroy() {
        Log.i("kwmp", "onDestroy()");
        super.onDestroy();
    }
}
