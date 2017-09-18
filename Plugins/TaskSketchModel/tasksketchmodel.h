#ifndef TASKSKETCHMODEL_H
#define TASKSKETCHMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "itasksketchmodel.h"
#include "../ExtendableDataManager/iextendabledatamanager.h"
#include "../TaskListModel/itasktreemodel.h"

//! \addtogroup TaskSketchModel_imp
//! \{
class TaskSketchModel : public QObject, ITaskSketchModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ITaskSketchModel)

public:
    TaskSketchModel();
    ~TaskSketchModel();

private:
    // Native part
    IExtendableDataManager *dataManager;
    ITaskTreeModel *myModel;
    QAbstractItemModel *taskModel;
    QAbstractItemModel *sketchItemModel;
    int myModelId;
    int activeViewId;
    int activeModelId;
    PluginInfo *pluginInfo;

    QList<PluginInfo*> childModelPlugins;
    QList<PluginInfo*> viewPlugins;

    // Unique part
    QString tableName;
    QString coreRelationName;

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
    bool Open(IModelPlugin *model) override;
    void Close() override;

    // ITaskSketchModel interface
public:
    QAbstractItemModel *GetModel() override;
    QAbstractItemModel *GetInternalModel() override;
    void ConvertSketchToTask(int sketchId) override;

signals:
    void OnClose(PluginInfo *model);
    void OnClose();

private:
    void SetupModel();
};
//! \}
#endif // TASKLISTMODEL_H
