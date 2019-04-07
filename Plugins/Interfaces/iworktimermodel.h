#ifndef IWorkTimer_H
#define IWorkTimer_H

#include <QtCore>

//!  \defgroup WorkTimer WorkTimer
//!      \ingroup Plugins
//!  \defgroup WorkTimer_int Interface
//!      \ingroup WorkTimer
//!  \defgroup WorkTimer_imp Implementation
//!      \ingroup WorkTimer
//!  \defgroup WorkTimer_dep Dependent plugins
//!      \ingroup WorkTimer

//!  \addtogroup WorkTimer_int
//!  \{
class IWorkTimer
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
//!  \}
Q_DECLARE_INTERFACE(IWorkTimer, "IWorkTimer")
#endif // IWorkTimer_H
