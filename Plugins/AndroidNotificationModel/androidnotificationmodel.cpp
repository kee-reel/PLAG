#include "androidnotificationmodel.h"

AndroidNotificationModel::AndroidNotificationModel()
{
    openedView = NULL;
    openedModel = NULL;
}

AndroidNotificationModel::~AndroidNotificationModel()
{
}

void AndroidNotificationModel::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void AndroidNotificationModel::OnAllSetup()
{

}

QString AndroidNotificationModel::GetLastError()
{

}

void AndroidNotificationModel::AddReferencePlugin(PluginInfo *pluginInfo)
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

void AndroidNotificationModel::ReferencePluginClosed(PluginInfo *pluginInfo)
{

}

bool AndroidNotificationModel::Open(IModelPlugin *parent)
{
    qDebug() << "AndroidNotificationModel open.";
    ShowNotification("AndroidNotificationModel says:", "Hi there!");
    ShowToast("Toast test");
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

void AndroidNotificationModel::Close()
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

void AndroidNotificationModel::ShowNotification(QString title, QString message, int id)
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

void AndroidNotificationModel::CancelNotification(int id)
{
//    public static void cancelNotification(int notifyId)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "cancelNotification",
                "(I)V",
                    jint(id));
}

void AndroidNotificationModel::ShowToast(const QString &message, Duration duration)
{
//    public static void showToast(String msg, int delay)
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "showToast",
                "(Ljava/lang/String;I)V",
                    javaMessage.object<jstring>(),
                    jint(duration));
}

void AndroidNotificationModel::PlanApplicationWakeup(TimeType type, QDateTime time)
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

void AndroidNotificationModel::SetAlarm(IAndroidNotificationModel::TimeType type, QDateTime time)
{
//    public static void setAlarm(int type, int time)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setAlarm",
                "(I;I)V",
                    jint(type),
                    jlong(time.toSecsSinceEpoch()));
}

void AndroidNotificationModel::SetRepeatingAlarm(IAndroidNotificationModel::TimeType type, QDateTime triggerTime, QDateTime interval)
{
//    public static void setRepeatingAlarm(int type, int triggerTime, int interval)
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "setRepeatingAlarm",
                "(I;I;I)V",
                    jint(type),
                    jlong(triggerTime.toSecsSinceEpoch()),
                    jlong(interval.toSecsSinceEpoch()));
}

void AndroidNotificationModel::CancelAlarm()
{
//    public static void cancelAlarm()
    QAndroidJniObject::callStaticMethod<void>("com/mass/mainapp/QtActivityExtention", "cancelAlarm");
}
