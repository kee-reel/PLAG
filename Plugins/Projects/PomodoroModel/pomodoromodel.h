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

#include "../../Interfaces/ipomodoromodel.h"
#include "../../Interfaces/iextendabledatamanager.h"
#include "../../Interfaces/itasktreemodel.h"
#include "../../Interfaces/inotificationmanagermodel.h"

//! \addtogroup PomodoroModel_imp
//! \{
class PomodoroModel : public PluginBase, IPomodoroModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPlugin IPomodoroModel)

public:
    PomodoroModel();
    virtual ~PomodoroModel() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private:
    // Native part
    IExtendableDataManager *dataManager;
    ITaskTreeModel *myModel;
    INotificationManagerModel *notificationManager;
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

    // IPomodoroModel interface
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
