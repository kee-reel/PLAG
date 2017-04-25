#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>\

#include "itasktreemodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

class TaskTreeModel : public QObject, ITaskTreeModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ITaskTreeModel)

public:
    TaskTreeModel();
    ~TaskTreeModel();

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginModel interface
public:
    void AddDataManager(QObject *) override;
    void AddParentModel(QObject *model, MetaInfo *meta);
    void AddChildModel(IModelPlugin *, MetaInfo *) override;
    void AddView(IViewPlugin *view, MetaInfo *meta) override;
    bool Open(IModelPlugin *parent, QWidget *parentWidget) override;
    bool CloseFromView(IViewPlugin *view) override;
    void ChildSelfClosed(IModelPlugin *child) override;

    // ITaskListModel interface
public:
    QString GetDataName() override;
    QAbstractItemModel *GetTreeModel() override;

private:
    void SetupModel();

    // Native part
    IModelPlugin *myParent;
    QWidget *myParentWidget;
    IViewPlugin *activeView;
    IModelPlugin *activeModel;

    template <class T>
    struct PluginInfo
    {
        T *plugin;
        MetaInfo *meta;
    };

    QList< PluginInfo<IModelPlugin> > childModelPlugins;
    QList< PluginInfo<IViewPlugin> > viewPlugins;

    // Unique part
    QString tableName;
    QString relationName;
    IExtendableDataBaseManagerPlugin* dataManager;
    QAbstractItemModel *treeModel;

signals:
    void OpenTaskEdit(int id);
};

#endif // TASKLISTMODEL_H
