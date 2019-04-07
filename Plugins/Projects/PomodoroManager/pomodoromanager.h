#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>
#include <QTimer>
#include <QVariant>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/ipomodoromanager.h"
#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/iusertaskmanager.h"
#include "../../Interfaces/inotificationmanager.h"

//! \addtogroup PomodoroManager_int
//! \{
class PomodoroManager : public PluginBase, IPomodoroManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin IPomodoroManager)

public:
    PomodoroManager();
    virtual ~PomodoroManager() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private:
    // Native part
    IExtendableDataManager *dataManager;
    IUserTaskManager *myModel;
    INotificationManager *notificationManager;
    QAbstractItemModel *taskModel;

    // Unique part
    QString tableName;
    QString coreRelationName;

    WorkSetup workSetup;
    QModelIndex currentTask;
    QModelIndex finishedPomodoros;
    QTimer periodsTimer;
    int notificationTimerId;

private slots:
    void OnTimerEnded(int timerId);

    // IPomodoroManager interface
public:
    QAbstractItemModel *GetTaskModel() override;
    void SetActiveProject(QModelIndex index) override;
    QModelIndex* GetActiveProject() override;
    WorkSetup GetWorkSetup() override;
public slots:
    void StartPomodoro() override;
signals:
    void OnPomodoroFinished();
    void RestFinished();
};
//! \}
#endif // TASKLISTMODEL_H
