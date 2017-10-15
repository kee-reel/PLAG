#include "notificationmanagermodel.h"

#include <QDebug>

NotificationManagerModel::NotificationManagerModel()
{
    openedView = NULL;
    openedModel = NULL;
//    NotificationManagerModel::SetInstance(this);
}

NotificationManagerModel::~NotificationManagerModel()
{
}

void NotificationManagerModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void NotificationManagerModel::OnAllSetup()
{
#ifdef Q_OS_ANDROID
    RegisterNativeMethods();
#endif
}

QString NotificationManagerModel::GetLastError()
{

}

void NotificationManagerModel::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type){
    case PLUGINVIEW:{
        relatedViewPlugins.append(pluginInfo);
        qDebug() << "New IViewPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(pluginInfo->Instance, SIGNAL( OnClose(PluginInfo*) ), SLOT( ReferencePluginClosed(PluginInfo*) ));
    } break;

    case PLUGINMODEL:{
        relatedModelPlugins.append(pluginInfo);
        qDebug() << "New IModelPlugin added (" << pluginInfo->Meta->Name << ").";
        connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
    } break;

    case ROOTMODEL:{
        pluginInfo->Plugin.model->AddReferencePlugin(this->pluginInfo);
    } break;

    case DATAMANAGER:{

    }break;
    }
}

void NotificationManagerModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool NotificationManagerModel::Open(IModelPlugin *parent)
{
    qDebug() << "AndroidNotificationModel open.";
    if(relatedViewPlugins.count() == 0){
        qDebug() << "!AndroidNotificationModel hasn't any views!";
        return false;
    }

    openedView = relatedViewPlugins.first();
    qDebug() << "AndroidNotificationModel opens related view " << openedView->Meta->Name;
    if(!openedView->Plugin.view->Open(this)){
        qDebug() << "!Can't open first view!";
        openedView = NULL;
        return false;
    }
    return true;
}

void NotificationManagerModel::Close()
{
    qDebug() << "AndroidNotificationModel close.";
    if(openedView != NULL && !openedView->Plugin.view->Close()){
        qDebug() << "View plugin" << openedView->Meta->Name
                 << "not closed, but model closing anyway.";
    }
    if(openedModel != NULL)
        openedView->Plugin.view->Close();

    openedView = NULL;
    openedModel = NULL;
    emit OnClose(pluginInfo);
    emit OnClose();
}

#ifdef Q_OS_ANDROID
static bool isTriggered = false;

void NotificationManagerModel::ShowNotification(QString title, QString message, int id)
{
    QAndroidJniObject javaTitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);

//    public static void showNotification(String title, String message, int notifyId)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "showNotification",
                "(Ljava/lang/String;Ljava/lang/String;I)V",
                    javaTitle.object<jstring>(),
                    javaMessage.object<jstring>(),
                    jint(id));
}

void NotificationManagerModel::CancelNotification(int id)
{
//    public static void cancelNotification(int notifyId)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "cancelNotification",
                "(I)V",
                    jint(id));
}

void NotificationManagerModel::ShowToast(const QString &message, Duration duration)
{
//    public static void showToast(String msg, int delay)
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "showToast",
                "(Ljava/lang/String;I)V",
                    javaMessage.object<jstring>(),
                    jint(duration));
}

void NotificationManagerModel::PlanApplicationWakeup(TimeType type, QDateTime time)
{
    auto activity = QtAndroid::androidActivity();
    auto packageManager = activity.callObjectMethod("getPackageManager",
                                                    "()Landroid/content/pm/PackageManager;");

    auto activityIntent = packageManager.callObjectMethod("getLaunchIntentForPackage",
                                                          "(Ljava/lang/String;)Landroid/content/Intent;",
                                                          activity.callObjectMethod("getPackageName",
                                                          "()Ljava/lang/String;").object());

    auto pendingIntent = QAndroidJniObject::callStaticObjectMethod("android/app/PendingIntent", "getActivity",
                                                                   "(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
                                                                   activity.object(), jint(0), activityIntent.object(),
                                                                   QAndroidJniObject::getStaticField<jint>("android/content/Intent",
                                                                                                           "FLAG_ACTIVITY_CLEAR_TOP"));

    auto alarmManager = activity.callObjectMethod("getSystemService",
                                                  "(Ljava/lang/String;)Ljava/lang/Object;",
                                                  QAndroidJniObject::getStaticObjectField("android/content/Context",
                                                                                          "ALARM_SERVICE",
                                                                                          "Ljava/lang/String;").object());

    alarmManager.callMethod<void>("set", "(IJLandroid/app/PendingIntent;)V",
                                    jint(type),
                                    jlong(time.toMSecsSinceEpoch()),
                                    pendingIntent.object());
}

int NotificationManagerModel::SetAlarm(INotificationManagerModel::TimeType type, QDateTime time)
{
    qDebug() << "SET ALARM" << time.toSecsSinceEpoch();
//    public static void setAlarm(int type, int time)
    auto activity = QtAndroid::androidActivity();
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarm",
                "(IJ)V",
                    jint(type),
                    jlong(time.toMSecsSinceEpoch()));
    delayedCallbackTimer.start();
}

int NotificationManagerModel::SetRepeatingAlarm(INotificationManagerModel::TimeType type, QDateTime triggerTime, QDateTime interval)
{
    qDebug() << "SET" << triggerTime.toSecsSinceEpoch() << interval.toSecsSinceEpoch();
//    public static void setRepeatingAlarm(int type, int triggerTime, int interval)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setRepeatingAlarm",
                "(IJJ)V",
                    jint(type),
                    jlong(triggerTime.toMSecsSinceEpoch()),
                    jlong(interval.toMSecsSinceEpoch()));
    delayedCallbackTimer.start();
}

void NotificationManagerModel::SetAlarmedNotification(INotificationManagerModel::TimeType type, QDateTime time, QString title, QString message, int id)
{
    QAndroidJniObject javaTitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
//    public static void setAlarmedNotification(int type, long time, String title, String message, int notifyId)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarmedNotification",
                "(IJLjava/lang/String;Ljava/lang/String;I)V",
                    jint(type),
                    jlong(time.toMSecsSinceEpoch()),
                    javaTitle.object<jstring>(),
                    javaMessage.object<jstring>(),
                    jint(id));
}

void NotificationManagerModel::setAlarmedToast(INotificationManagerModel::TimeType type, QDateTime time, const QString &message, INotificationManagerModel::Duration duration)
{
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
//    public static void setAlarmedToast(int type, long time, String message, int delay)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarmedToast",
                "(IJLjava/lang/String;I)V",
                    jint(type),
                    jlong(time.toMSecsSinceEpoch()),
                    javaMessage.object<jstring>(),
                    jint(duration));
}

void NotificationManagerModel::CancelAlarm()
{
//    public static void cancelAlarm()
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "cancelAlarm");
}


void NotificationManagerModel::OnAndroidAlarmRecieved(JNIEnv *, jobject)
{
    qDebug() << "OnAndroidAlarmRecieved" << &isTriggered << isTriggered;
    isTriggered = true;
}

void NotificationManagerModel::CheckTimerTimeout()
{
    qDebug() << "~TIMEOUT" << &isTriggered << isTriggered;
    if(isTriggered)
    {
        isTriggered = false;
        delayedCallbackTimer.stop();
        emit OnTimerTimeout(0);
    }
}

void NotificationManagerModel::RegisterNativeMethods()
{
    qDebug() << "~Start";
    JNINativeMethod methods[] {
        { "OnAndroidAlarmRecieved", // const char* function name;
            "()V", // const char* function signature
            (void *)&NotificationManagerModel::OnAndroidAlarmRecieved // function pointer
        }
    };

    QAndroidJniEnvironment env;
    qDebug() << "~JVM" << env.javaVM();

    QAndroidJniObject javaClass = QtAndroid::androidActivity();// ("my/java/project/FooJavaClass");
    jclass objectClass = env->GetObjectClass(javaClass.object<jobject>());
    qDebug() << "~objectClass" << objectClass;
    if(env->ExceptionCheck())
    {
        qDebug() << "~Exception:";
        env->ExceptionClear();
        return;
    }

    env->RegisterNatives(objectClass,
                         methods,
                         sizeof(methods) / sizeof(methods[0]));
    if(env->ExceptionCheck())
    {
        qDebug() << "~Exception:";
        env->ExceptionClear();
        return;
    }
    env->DeleteLocalRef(objectClass);

    delayedCallbackTimer.setInterval(1000);
    connect(&delayedCallbackTimer, SIGNAL(timeout()), this, SLOT(CheckTimerTimeout()));
}
#endif

#if (defined(Q_OS_WIN))
void NotificationManagerModel::ShowNotification(QString title, QString message, int id)
{

}

void NotificationManagerModel::CancelNotification(int id)
{

}

void NotificationManagerModel::ShowToast(const QString &message, Duration duration)
{

}

void NotificationManagerModel::PlanApplicationWakeup(TimeType type, QDateTime time)
{

}

int NotificationManagerModel::SetAlarm(INotificationManagerModel::TimeType type, QDateTime time)
{
    QExtendedTimer *newTimer = new QExtendedTimer(this);
    switch (type) {
    case INotificationManagerModel::RTC_TIME:{
        qint64 remainingTime = QDateTime::currentDateTime().msecsTo(time);
        newTimer->setSingleShot(true);
        newTimer->setInterval(remainingTime);
    } break;
    case INotificationManagerModel::FROM_DEVICE_START:

        break;
    default:
        break;
    }

    newTimer->start();
    int timerId = timersDictionary.count();
    connect(newTimer, &QExtendedTimer::timeout, this,
            [this, newTimer](QExtendedTimer *timer)
    {
        int timerId = timersDictionary[timer];
        if(timer->isSingleShot())
        {
            timersDictionary.remove(timer);
            delete timer;
        }
        emit OnTimerTimeout(timerId);
    });
    timersDictionary.insert(newTimer, timerId);
    return timerId;

}

int NotificationManagerModel::SetRepeatingAlarm(INotificationManagerModel::TimeType type, QDateTime triggerTime, QDateTime interval)
{

}

void NotificationManagerModel::CancelAlarm()
{

}
#endif
