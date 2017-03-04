#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "itasktreemodel.h"
#include "tasktreeitemmodel.h"
#include "../ExtendableDataBaseManager/iextendabledatabasemanagerplugin.h"

class TaskTreePluginModel : public QObject, ITreeModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IModelPlugin ITreeModel)

public:
    TaskTreePluginModel();
    ~TaskTreePluginModel();

private:
    // Native part
    IModelPlugin *myParent;
    QWidget *myParentWidget;
    int myModelId;
    int activeViewId;
    int activeModelId;

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
    IExtendableDataBaseManagerPlugin* dataManager;
    TaskTreeItemModel* treeModel;

    // IPlugin interface
public:
    void OnAllSetup() override;
    QString GetLastError() override;

    // IPluginModel interface
public:
    void AddChildModel(IModelPlugin *, MetaInfo *);
    void AddDataManager(QObject *);
    void AddView(IViewPlugin *plugin, MetaInfo *meta);
    bool Open(IModelPlugin *parent, QWidget *parentWidget, int id);
    bool Close();
    void ChildSelfClosed(int id);
    QString GetError();

    // ITaskListModel interface
public:
    QAbstractItemModel *GetTreeModel() override;
};

#endif // TASKLISTMODEL_H
