#include "notificationmanager.h"

#if (defined(Q_OS_UNIX))
void NotificationManager::ShowNotification(QString title, QString message, int id)
{
}

void NotificationManager::CancelNotification(int id)
{
}

void NotificationManager::ShowToast(const QString &message, Duration duration)
{
}

void NotificationManager::PlanApplicationWakeup(TimeType type, QDateTime time)
{
}

int NotificationManager::SetAlarm(INotificationManager::TimeType type, QDateTime time)
{
    QExtendedTimer *newTimer = new QExtendedTimer(this);

    switch (type)
    {
        case INotificationManager::RTC_TIME:
        {
            qint64 remainingTime = QDateTime::currentDateTime().msecsTo(time);
            newTimer->setSingleShot(true);
            newTimer->setInterval(remainingTime);
        } break;

        case INotificationManager::FROM_DEVICE_START:
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

int NotificationManager::SetRepeatingAlarm(INotificationManager::TimeType type, QDateTime triggerTime, QDateTime interval)
{
}

void NotificationManager::CancelAlarm()
{
}

void NotificationManager::SetAlarmedNotification(INotificationManager::TimeType type, QDateTime time, QString title,
        QString message, int id)
{
}

void NotificationManager::SetAlarmedToast(INotificationManager::TimeType type, QDateTime time, const QString &message,
        INotificationManager::Duration duration)
{
}
#endif
