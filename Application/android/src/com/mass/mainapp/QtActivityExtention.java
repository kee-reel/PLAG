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
import java.util.Calendar;
import java.util.Date;

public class QtActivityExtention extends QtActivity
{
    // Native functions
    public static native void OnAndroidAlarmRecieved();

    private static final String TAG = "QtActivityExtention";
    private static QtActivityExtention instance;

    private static NotificationManager notificationManager;
    private static Notification.Builder notificationBuilder;

    private static PendingIntent contentIntent;
    private static PendingIntent pendingIntent;

    private static String plannedTitle;
    private static String plannedMessage;
    private static int plannedNotificationId;
    private static int plannedToastDuration;
    private enum PlannedAlarmEvent{
        NONE,
        NOTIFICATION,
        TOAST
    }
    private static PlannedAlarmEvent plannedAlarmEvent;

    public QtActivityExtention() { instance = this; }

@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        notificationBuilder = new Notification.Builder(instance);
        notificationBuilder
//            .setContentIntent(contentIntent)
            .setSmallIcon(R.drawable.icon);
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

    public static void setAlarm(int type, long time) {
        Log.i(TAG, "setAlarm");
        cancelAlarm();
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        Intent alarmIntent = new Intent(instance, AlarmReceiver.class);
        pendingIntent = PendingIntent.getBroadcast(instance, 0, alarmIntent, 0);
        manager.set(type, time, pendingIntent);
    }

    public static void setRepeatingAlarm(int type, long triggerTime, long interval) {
        Log.i(TAG, "setRepeatingAlarm");
        cancelAlarm();
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        Intent alarmIntent = new Intent(instance, AlarmReceiver.class);
        pendingIntent = PendingIntent.getBroadcast(instance, 0, alarmIntent, 0);
        manager.setRepeating(type, triggerTime, interval, pendingIntent);
    }

    public static void cancelAlarm() {
        Log.i(TAG, "cancelAlarm");
        AlarmManager manager = (AlarmManager)instance.getSystemService(Context.ALARM_SERVICE);
        manager.cancel(pendingIntent);
    }

    public static void processAlarm() {
        Log.i(TAG, "processAlarm");
        switch(plannedAlarmEvent)
        {
            case NOTIFICATION:
                showNotification(plannedTitle, plannedMessage, plannedNotificationId);
                break;
            case TOAST:
                showToast(plannedMessage, plannedToastDuration);
                break;
        }

        plannedAlarmEvent = PlannedAlarmEvent.NONE;
        OnAndroidAlarmRecieved();
    }

    public static void setAlarmedNotification(int type, long time, String title, String message, int notifyId)
    {
        Log.i(TAG, "setAlarmedNotification");
        plannedAlarmEvent = PlannedAlarmEvent.NOTIFICATION;
        plannedTitle = title;
        plannedMessage = message;
        plannedNotificationId = notifyId;
        setAlarm(type, time);
    }

    public static void setAlarmedToast(int type, long time, String message, int delay)
    {
        Log.i(TAG, "setAlarmedToast");
        plannedAlarmEvent = PlannedAlarmEvent.TOAST;
        plannedMessage = message;
        plannedToastDuration = delay;
        setAlarm(type, time);
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
}
