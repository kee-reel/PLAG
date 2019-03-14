#ifndef ITIMERMODEL_H
#define ITIMERMODEL_H

#include "../../interfaces.h"

//! defgroup TimerModel
//!     ingroup MainMenuPlugin_rel_m
//! defgroup TimerModel_int Interface
//!     ingroup TimerModel
//! defgroup TimerModel_imp Implementation
//!     ingroup TimerModel

//! addtogroup TimerModel_int
//! {
class ITimerModel :
    public IModelPlugin
{
public:
    ///
    /// \brief Start timer with no interval. Run until it will be stoped with StopTimer().
    ///
    int StartTimer();
    ///
    /// \brief Start timer with interval. It will be stoped after given time passed.
    /// \param interval
    ///
    int StartTimer(int intervalInSeconds);
    void StopTimer();

signals:
    ///
    /// \brief Calls every second when timer started.
    ///
    void SecondTick();
};
//! }
Q_DECLARE_INTERFACE(ITimerModel, "ITimerModel")
#endif // ITIMERMODEL_H
