#ifndef IPOMODOROMODEL_H
#define IPOMODOROMODEL_H

#include "../../interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class QModelIndex;
class QTimer;
class QDateTime;

//! \defgroup PomodoroModel
//!     \ingroup MainMenuPlugin_rel_m
//! \defgroup PomodoroModel_int Interface
//!     \ingroup PomodoroModel
//! \defgroup PomodoroModel_imp Implementation
//!     \ingroup PomodoroModel

//! \addtogroup PomodoroModel_int
//! \{
class IPomodoroModel: public IModelPlugin
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
//! \}
Q_DECLARE_INTERFACE(IPomodoroModel, "IPomodoroModel v0.1")
#endif // ITASKLISTMODEL_H
