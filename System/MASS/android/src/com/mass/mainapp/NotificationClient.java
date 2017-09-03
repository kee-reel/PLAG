package com.mass.mainapp;

import org.qtproject.qt5.android.bindings.QtActivity;
import android.app.Activity;
import android.app.AlarmManager;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;
import android.os.Bundle;
import android.os.Looper;
import android.os.Handler;
import android.util.Log;
import java.lang.String;

public class NotificationClient extends QtActivity
{
    private static final String TAG = "QtActivityExtention";

    private static NotificationManager m_notificationManager;
    private static Notification.Builder m_builder;
    private static NotificationClient m_instance;
    private static PendingIntent pendingIntent;

    public NotificationClient()
    {
        m_instance = this;
    }

@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        m_notificationManager = (NotificationManager)m_instance.getSystemService(Context.NOTIFICATION_SERVICE);
        m_builder = new Notification.Builder(m_instance);
        m_builder.setSmallIcon(R.drawable.icon);

        /* Retrieve a PendingIntent that will perform a broadcast */
        Intent alarmIntent = new Intent(m_instance, AlarmReceiver.class);
        pendingIntent = PendingIntent.getBroadcast(m_instance, 0, alarmIntent, 0);
    }

@Override
    public void onDestroy()
    {
        super.onDestroy();
    }

@Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);
    }

    public static void notify(String title, String message)
    {
        Log.i(TAG, "NOTIFY CALLED!");
        m_builder.setContentTitle(title);
        m_builder.setContentText(message);
        m_notificationManager.notify(1, m_builder.build());
        m_instance.makeToast("Test!");
        start();
    }

    public static void start() {
        AlarmManager manager = (AlarmManager)m_instance.getSystemService(Context.ALARM_SERVICE);
        int interval = 8000;

        manager.setInexactRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), interval, pendingIntent);
        MakeToast("Alarm set!");
    }

    public static void cancel() {
        AlarmManager manager = (AlarmManager)m_instance.getSystemService(Context.ALARM_SERVICE);
        manager.cancel(pendingIntent);
        MakeToast("Alarm Canceled");
    }

    public static void MakeToast(String msg)
    {
        m_instance.makeToast(msg);
    }

    private void makeToast(String msg)
    {
        final String tmpStr = msg;
        runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                Toast.makeText(NotificationClient.this, tmpStr, Toast.LENGTH_LONG).show();
            }
        });
    }
}
