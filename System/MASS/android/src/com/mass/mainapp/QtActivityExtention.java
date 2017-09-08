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

public class QtActivityExtention extends QtActivity
{
    private static final String TAG = "QtActivityExtention";
    private static QtActivityExtention instance;

    private static NotificationManager notificationManager;
    private static Notification.Builder notificationBuilder;

    private static PendingIntent contentIntent;
    private static PendingIntent pendingIntent;

    public QtActivityExtention() { instance = this; }

@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

//        Intent intent = new Intent(instance, QtActivityExtention.class);
//        contentIntent = PendingIntent.getActivity(instance, 0, intent, PendingIntent.FLAG_CANCEL_CURRENT);
        notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        notificationBuilder = new Notification.Builder(instance);
        notificationBuilder
//            .setContentIntent(contentIntent)
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

    public static void showNotification(String title, String message, int notifyId)
    {
        Log.i(TAG, "showNotification");
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
        Log.i(TAG, "cancelNotification");
        notificationManager.cancel(notifyId);
    }

    public static void showToast(String msg, int delay)
    {
        Log.i(TAG, "showToast");
        final String tmpStr = msg;
        final int tmpDelay = delay;
        instance.runOnUiThread(new Runnable()
        {
            @Override
            public void run()
            {
                Toast.makeText(instance, tmpStr, tmpDelay).show();
            }
        });
    }

    public static void setAlarm(int type, int time) {
        Log.i(TAG, "setAlarm");
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        manager.set(type, time, pendingIntent);
    }

    public static void setRepeatingAlarm(int type, int triggerTime, int interval) {
        Log.i(TAG, "setRepeatingAlarm");
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        manager.setRepeating(type, triggerTime, interval, pendingIntent);
    }

    public static void cancelAlarm() {
        Log.i(TAG, "cancelAlarm");
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        manager.cancel(pendingIntent);
    }
}
