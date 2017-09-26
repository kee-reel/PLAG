#ifndef IPOMODOROMODEL_H
#define IPOMODOROMODEL_H

#include "../MainMenuModelPlugin/interfaces.h"

template <class A>
class QVector;
class QAbstractItemModel;
class QModelIndex;
class QTimer;

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
signals:
    void PomodoroFinished();
};
//! \}
Q_DECLARE_INTERFACE(IPomodoroModel, "IPomodoroModel v0.1")
#endif // ITASKLISTMODEL_H
