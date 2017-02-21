#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "itasklistmodel.h"
#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"

class TaskListModel : public QObject, ITaskListModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginModel ITaskListModel)
    QString tableName = "TaskList";
public:
    TaskListModel();
    ~TaskListModel();

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

    ITaskDataManagerPlugin* dataManager;
    ITaskListModel::TaskInfo *rootTask;

    ITaskDataManagerPlugin::TaskInfo ConvertToManagerTaskInfo(TaskInfo &task);
    void DeleteTaskRecursive(TaskInfo *task);

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
    TaskInfo *GetRootTask() override;
    bool AddTask(TaskInfo *taskParent, TaskInfo taskData) override;
    bool EditTask(TaskInfo *task, TaskInfo taskData) override;
    bool DeleteTask(TaskInfo *task) override;
};

#endif // TASKLISTMODEL_H
