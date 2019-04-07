#ifndef IPomodoroManager_H
#define IPomodoroManager_H

#include <QtCore>

template <class A>
class QVector;
class QAbstractItemModel;
class QModelIndex;
class QTimer;
class QDateTime;

//!  \defgroup PomodoroManager PomodoroManager
//!      \ingroup Plugins
//! \defgroup PomodoroManager_int Interface
//!     \ingroup PomodoroManager
//! \defgroup PomodoroManager_imp Implementation
//!     \ingroup PomodoroManager
//!  \defgroup PomodoroManager_dep Dependent plugins
//!      \ingroup PomodoroManager

//! \addtogroup PomodoroManager_int
//!  \{
class IPomodoroManager
{
public:
    struct WorkSetup{
        int workSessionDuration;
        int easyRestDuration;
        int longRestDuration;
        int longRestPeriod;
    };

    virtual QAbstractItemModel* GetTaskModel() = 0;
    virtual void SetActiveProject(QModelIndex) = 0;
    virtual QModelIndex* GetActiveProject() = 0;
    virtual WorkSetup GetWorkSetup() = 0;
public slots:
    virtual void StartPomodoro() = 0;
signals:
    void OnPomodoroFinished();
};
//!  \}
Q_DECLARE_INTERFACE(IPomodoroManager, "IPomodoroManager v0.1")
#endif // ITASKLISTMODEL_H
