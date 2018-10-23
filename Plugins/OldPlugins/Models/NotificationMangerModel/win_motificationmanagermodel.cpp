#include "notificationmanagermodel.h"

#if (defined(Q_OS_WIN))
void NotificationManagerModel::OnAllSetup()
{
}

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

    switch (type)
    {
        case INotificationManagerModel::RTC_TIME:
        {
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

void NotificationManagerModel::SetAlarmedNotification(INotificationManagerModel::TimeType type, QDateTime time, QString title,
        QString message, int id)
{
}

void NotificationManagerModel::SetAlarmedToast(INotificationManagerModel::TimeType type, QDateTime time, const QString &message,
        INotificationManagerModel::Duration duration)
{
}
#endif
