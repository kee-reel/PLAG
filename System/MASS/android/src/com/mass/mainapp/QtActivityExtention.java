package com.mass.mainapp;

import org.qtproject.qt5.android.bindings.QtActivity;
import android.app.Activity;
import android.app.AlarmManager;
import android.support.v4.app;
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

public class QtActivityExtention extends QtActivity
{
    private static final String TAG = "QtActivityExtention";
    private static QtActivityExtention instance;

    private static NotificationManagerCompat notificationManager;
    private static NotificationCompat.Builder notificationBuilder;

    private static PendingIntent pendingIntent;

    public NotificationClient()
    {
        instance = this;
    }

@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        notificationManager = NotificationManagerCompat.from(instance);
        notificationBuilder = new NotificationCompat.Builder(instance);
        notificationBuilder
            .setContentIntent(contentIntent)
            .setSmallIcon(R.drawable.icon);

        /* Retrieve a PendingIntent that will perform a broadcast */
        Intent alarmIntent = new Intent(instance, AlarmReceiver.class);
        pendingIntent = PendingIntent.getBroadcast(instance, 0, alarmIntent, 0);
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

    public static void showNotification(int notifyId, String title, String message)
    {
        notificationBuilder
            .setContentTitle(title)
            .setContentText(message)
            .setTicker(message);

        Notification notification = notificationBuilder.build();
        notification.defaults = Notification.DEFAULT_SOUND | Notification.DEFAULT_VIBRATE;
        notificationManager.notify(notifyId, notification);
    }

    public static void cancelNotification(int notifyId)
    {
        notificationManager.cancel(notifyId);
    }

    public static void showToast(String msg, int delay)
    {
        final String tmpStr = msg;
        runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                Toast.makeText(NotificationClient.this, tmpStr, delay).show();
            }
        });
    }

    public static void start() {
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        int interval = 8000;

        manager.setInexactRepeating(AlarmManager.RTC_WAKEUP, System.currentTimeMillis(), interval, pendingIntent);
        MakeToast("Alarm set!");
    }

    public static void cancel() {
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        manager.cancel(pendingIntent);
        MakeToast("Alarm Canceled");
    }
}
