#ifndef ANDROIDNOTIFICATIONMODEL_H
#define ANDROIDNOTIFICATIONMODEL_H

#include <QtCore>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QList>
#include <QDebug>

#ifdef Q_OS_ANDROID
    #include <QtAndroid>
    #include <QAndroidJniEnvironment>
#endif

#include "../../Common/plugin_base.h"

#include "../../Interfaces/inotificationmanagermodel.h"
#include "qextendedtimer.h"

//! addtogroup AndroidNotificationModel_imp
//! {
class NotificationManagerModel : public PluginBase, INotificationManagerModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        INotificationManagerModel
    )

public:
    NotificationManagerModel();
    virtual ~NotificationManagerModel() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

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
    QMap<QExtendedTimer*, int> timersDictionary;
};

//! }
#endif // ANDROIDNOTIFICATIONMODEL_H
