#ifndef ANDROIDNOTIFICATIONMODEL_H
#define ANDROIDNOTIFICATIONMODEL_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QList>
#include <QDebug>

#ifdef Q_OS_ANDROID
    #include <QtAndroid>
    #include <QAndroidJniEnvironment>
#endif

#include "inotificationmanagermodel.h"
#include "qextendedtimer.h"

//! addtogroup AndroidNotificationModel_imp
//! {
class NotificationManagerModel : public QObject, INotificationManagerModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IModelPlugin
        INotificationManagerModel
    )

public:
    NotificationManagerModel();
    ~NotificationManagerModel();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;

    // IAndroidNotificationModel interface
public:
    void ShowNotification(QString title, QString message, int id = 0) override;
    void CancelNotification(int id) override;
    void ShowToast(const QString &message, INotificationManagerModel::Duration duration = LONG) override;
    void PlanApplicationWakeup(TimeType timePlan, QDateTime secs) override;
    int SetAlarm(TimeType type, QDateTime time) override;
    int SetRepeatingAlarm(TimeType type, QDateTime triggerTime, QDateTime interval) override;
    void SetAlarmedNotification(TimeType type, QDateTime time, QString title, QString message, int id) override;
    void SetAlarmedToast(TimeType type, QDateTime time, const QString &message, INotificationManagerModel::Duration duration) override;
    void CancelAlarm() override;

#ifdef Q_OS_ANDROID
public:
    void OnAndroidAlarmRecieved(JNIEnv */*env*/, jobject /*obj*/);
private:
    void RegisterNativeMethods();
    QTimer delayedCallbackTimer;
private slots:
    void CheckTimerTimeout();
#endif

signals:
    void OnTimerTimeout(int);

private:
    QWidget *referenceWidget;
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;
    QMap<QExtendedTimer*, int> timersDictionary;
};

//! }
#endif // ANDROIDNOTIFICATIONMODEL_H
