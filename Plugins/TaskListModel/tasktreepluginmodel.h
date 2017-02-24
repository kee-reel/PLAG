#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "itasktreemodel.h"
#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"
#include "tasktreeitemmodel.h"

class TaskTreePluginModel : public QObject, ITaskTreeModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginModel ITaskTreeModel)

public:
    TaskTreePluginModel();
    ~TaskTreePluginModel();

private:
    // Native part
    IPluginModel *myParent;
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

    QList< PluginInfo<IPluginModel> > childModelPlugins;
    QList< PluginInfo<IPluginView> > viewPlugins;

    // Unique part
    QString tableName;
    ITreeDataManagerPlugin* dataManager;
    TaskTreeItemModel* treeModel;

    // IPluginModel interface
public:
    void AddChildPlugin(IPluginModel *, MetaInfo *);
    void SetDataManager(QObject *);
    void AddView(IPluginView *plugin, MetaInfo *meta);
    bool Open(IPluginModel *parent, QWidget *parentWidget, int id);
    bool Close();
    void ChildSelfClosed(int id);
    QString GetError();

    // ITaskListModel interface
public:
    QAbstractItemModel *GetTaskTree() override;

};

#endif // TASKLISTMODEL_H
