#ifndef IWORKTIMERMODEL_H
#define IWORKTIMERMODEL_H

#include "../../interfaces.h"

//! defgroup WorkTimerModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup WorkTimerModel_int Interface
//!     ingroup WorkTimerModel
//! defgroup WorkTimerModel_imp Implementation
//!     ingroup WorkTimerModel

//! addtogroup WorkTimerModel_int
//! {
class IWorkTimerModel :
        public IModelPlugin
{
public:
    ///
    /// \brief Start timer with no interval. Run until it will be stoped with StopTimer().
    ///
    void StartTimer();
    ///
    /// \brief Start timer with interval. It will be stoped after given time passed.
    /// \param interval
    ///
    void StartTimer(int intervalInSeconds);
    void StopTimer();

signals:
    ///
    /// \brief Calls every second when timer started.
    ///
    void SecondTick();
};
//! }
Q_DECLARE_INTERFACE(IWorkTimerModel, "IWorkTimerModel")
#endif // IWORKTIMERMODEL_H
