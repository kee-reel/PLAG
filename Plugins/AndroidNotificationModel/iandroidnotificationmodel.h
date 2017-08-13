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
    // Write your interface methods here
    virtual void PushNotification(QString message) = 0;
};
//! }
Q_DECLARE_INTERFACE(IAndroidNotificationModel, "IAndroidNotificationModel")
#endif // IANDROIDNOTIFICATIONMODEL_H
