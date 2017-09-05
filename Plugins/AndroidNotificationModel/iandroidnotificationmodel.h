#ifndef IANDROIDNOTIFICATIONMODEL_H
#define IANDROIDNOTIFICATIONMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

//! defgroup AndroidNotificationModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup AndroidNotificationModel_int Interface
//!     ingroup AndroidNotificationModel
//! defgroup AndroidNotificationModel_imp Implementation
//!     ingroup AndroidNotificationModel

//! addtogroup AndroidNotificationModel_int
//! {
class IAndroidNotificationModel :
        public IModelPlugin
{
public:
    enum Duration {
        SHORT = 0,
        LONG = 1
    };

    enum TimePlanning {
        UTC,
        FROM_DEVICE_START,
    };

    // Write your interface methods here
    virtual void ShowNotification(QString title, QString message, int id = 0) = 0;
    virtual void CancelNotification(int id = 0) = 0;
    virtual void ShowToast(const QString &message, IAndroidNotificationModel::Duration duration = LONG) = 0;
    virtual void PlanApplicationWakeup(TimePlanning timePlan, int secs) = 0;
    virtual void StartAlarm() = 0;
    virtual void CancelAlarm() = 0;
};
//! }
Q_DECLARE_INTERFACE(IAndroidNotificationModel, "IAndroidNotificationModel")
#endif // IANDROIDNOTIFICATIONMODEL_H
