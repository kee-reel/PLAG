#ifndef IANDROIDNOTIFICATIONMODEL_H
#define IANDROIDNOTIFICATIONMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

//! defgroup AndroidNotificationModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup AndroidNotificationModel_int Interface
//!     ingroup AndroidNotificationModel
//! defgroup AndroidNotificationModel_imp Implementation
//!     ingroup AndroidNotificationModel

class QDateTime;

//! addtogroup AndroidNotificationModel_int
//! {
class INotificationManagerModel :
        public IModelPlugin
{
public:
    enum Duration {
        SHORT = 0,
        LONG = 1
    };

    enum TimeType {
        RTC_TIME = 0,
        FROM_DEVICE_START = 2,
    };

    // Write your interface methods here
    virtual void ShowNotification(QString title, QString message, int id = 0) = 0;
    virtual void CancelNotification(int id = 0) = 0;
    virtual void ShowToast(const QString &message, INotificationManagerModel::Duration duration = LONG) = 0;
    virtual void PlanApplicationWakeup(TimeType timePlan, QDateTime time) = 0;
    virtual void SetAlarm(TimeType type, QDateTime time) = 0;
    virtual void SetRepeatingAlarm(TimeType type, QDateTime triggerTime, QDateTime interval) = 0;
    virtual void CancelAlarm() = 0;
};
//! }
Q_DECLARE_INTERFACE(INotificationManagerModel, "INotificationManagerModel")
#endif // IANDROIDNOTIFICATIONMODEL_H
