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
    PushNotification("AndroidNotificationModel says:", "Hi there!");
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

void AndroidNotificationModel::ShowNotification(int id, QString title, QString message)
{
    QAndroidJniObject javaTitle = QAndroidJniObject::fromString(title);
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);

    QAndroidJniObject::callStaticMethod<void>(CLASS_NAME, "showNotification",
                "(I;Ljava/lang/String;Ljava/lang/String;)V",
                    jint(id),
                    javaTitle.object<jstring>(),
                    javaMessage.object<jstring>());
}

void AndroidNotificationModel::CancelNotification(int id)
{
    QAndroidJniObject::callStaticMethod<void>(CLASS_NAME, "closeNotification",
                "(I;)V",
                    jint(id));
}

void AndroidNotificationModel::ShowToast(const QString &message, Duration duration)
{
    QAndroidJniObject javaMessage = QAndroidJniObject::fromString(message);
    QAndroidJniObject::callStaticMethod<void>(CLASS_NAME, "showToast",
                "(Ljava/lang/String;I)V",
                    javaMessage.object<jstring>(),
                    jint(duration));
}

void AndroidNotificationModel::PlanApplicationWakeup(TimePlanning timePlan, int secs)
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

    alarmManager.callMethod<void>("set",
                                  "(IJLandroid/app/PendingIntent;)V",
                                  QAndroidJniObject::getStaticField<jint>("android/app/AlarmManager", "RTC_WAKEUP"),
                                  jlong(QDateTime::currentMSecsSinceEpoch() + secs * 1000), pendingIntent.object());
}
