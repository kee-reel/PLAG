package com.mass.mainapp;

import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.PowerManager;
import android.widget.Toast;

public class AlarmReceiver extends BroadcastReceiver{

    final public static String ONE_TIME = "onetime";
    PowerManager.WakeLock wl;

@Override
    public void onReceive(Context context, Intent intent)
    {
        QtActivityExtention.processAlarm();
    }
}
