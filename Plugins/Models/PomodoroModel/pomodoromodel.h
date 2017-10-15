#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>
#include <QTimer>
#include <QVariant>

#include "ipomodoromodel.h"
#include "../../DataManagers/ExtendableDataManager/iextendabledatamanager.h"
#include "../../Models/TaskListModel/itasktreemodel.h"
#include "../../Models/NotificationMangerModel/inotificationmanagermodel.h"

//! \addtogroup PomodoroModel_imp
//! \{
class PomodoroModel : public QObject, IPomodoroModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin IPomodoroModel)

public:
    PomodoroModel();
    ~PomodoroModel();

private:
    // Native part
    IExtendableDataManager *dataManager;
    ITaskTreeModel *myModel;
    INotificationManagerModel *notificationManger;
    QAbstractItemModel *taskModel;
    int myModelId;
    int activeViewId;
    int activeModelId;
    PluginInfo *pluginInfo;

    QList< PluginInfo* > childModelPlugins;
    QList< PluginInfo* > viewPlugins;

    // Unique part
    QString tableName;
    QString coreRelationName;

    WorkSetup workSetup;
    QModelIndex currentTask;
    QModelIndex finishedPomodoros;
    QTimer periodsTimer;
    int notificationTimerId;

    void SetupModel();
private slots:
    void OnTimerEnded(int timerId);

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo *pointer);
    void OnClose();

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;

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
