#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractItemModel>

#include "itasktreemodel.h"
#include "../../DataManagers/ExtendableDataManager/iextendabledatamanager.h"

//! \addtogroup TaskTreeModel_imp
//! \{
class TaskTreeModel : public QObject, ITaskTreeModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ITaskTreeModel)

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
signals:
    void OnClose(PluginInfo *pluginInfo);
    void OnClose();

    // ITaskTreeModel interface
public:
    QAbstractItemModel *GetTreeModel();
signals:
    void OpenTaskEdit(int id);

public:
    TaskTreeModel();
    ~TaskTreeModel();

private:
    void SetupModel();

    // Native part
    IModelPlugin *myParent;
    IViewPlugin *activeView;
    IModelPlugin *activeModel;
    PluginInfo *pluginInfo;

    QList<PluginInfo*> childModelPlugins;
    QList<PluginInfo*> viewPlugins;

    // Unique part
    QString tableName;
    QString relationName;
    IExtendableDataManager* dataManager;
    QAbstractItemModel *treeModel;
};
//! \}
#endif // TASKLISTMODEL_H
