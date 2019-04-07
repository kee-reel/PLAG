#ifndef INOTIFICATIONMANAGER_H
#define INOTIFICATIONMANAGER_H

#include <QtCore>

//!  \defgroup NotificationManager NotificationManager
//!      \ingroup Plugins
//!  \defgroup NotificationManager_int Interface
//!      \ingroup NotificationManager
//!  \defgroup NotificationManager_imp Implementation
//!      \ingroup NotificationManager
//!  \defgroup NotificationManager_dep Dependent plugins
//!      \ingroup NotificationManager

class QDateTime;

//!  \addtogroup NotificationManager_int
//!  \{
class INotificationManager
{
public:
    enum Duration
    {
        SHORT = 0,
        LONG = 1
    };

    enum TimeType
    {
        RTC_TIME = 0,
        FROM_DEVICE_START = 2,
    };

    typedef void (*TimeoutFunc)(int);

    // Write your interface methods here
    virtual void ShowNotification(QString title, QString message, int id = 0) = 0;
    virtual void CancelNotification(int id = 0) = 0;
    virtual void ShowToast(const QString &message, INotificationManager::Duration duration = LONG) = 0;
    virtual void PlanApplicationWakeup(TimeType timePlan, QDateTime time) = 0;
    virtual int SetAlarm(TimeType type, QDateTime time) = 0;
    virtual int SetRepeatingAlarm(TimeType type, QDateTime triggerTime, QDateTime interval) = 0;
    virtual void SetAlarmedNotification(TimeType type, QDateTime time, QString title, QString message, int id = 0) = 0;
    virtual void SetAlarmedToast(TimeType type, QDateTime time, const QString &message,
                                 INotificationManager::Duration duration = LONG) = 0;
    virtual void CancelAlarm() = 0;

signals:
    void OnTimerTimeout(int);
};
//!  \}
Q_DECLARE_INTERFACE(INotificationManager, "INotificationManager")
#endif // INOTIFICATIONMANAGER_H
