#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>
#include <QDateTime>

#include "ipomodoromodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"
#include "../TaskListModel/itasktreemodel.h"

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
    IExtendableDataBaseManager *dataManager;
    ITaskTreeModel *myModel;
    QAbstractItemModel *taskModel;
    QAbstractItemModel *pomodoroItemModel;
    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;
    PluginInfo *pluginInfo;

    QList< PluginInfo* > childModelPlugins;
    QList< PluginInfo* > viewPlugins;

    // Unique part
    QString tableName;
    QString coreRelationName;
    int finishedPomodoros;

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model, QWidget *modelWidget) override;
    void Close() override;

    // IPomodoroModel interface
public:
    QAbstractItemModel *GetModel() override;
    QAbstractItemModel *GetInternalModel() override;
signals:
    void OnClose(PluginInfo *pointer);
    void OnClose();

private:
    void SetupModel();
};
//! \}
#endif // TASKLISTMODEL_H
