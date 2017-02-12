#ifndef TASKLISTMODEL_H
#define TASKLISTMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "itasklistmodel.h"
#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"

// TODO: Make recursive delete
//class ExtendedTaskInfo
//{
//public:
//    ITaskListModel::TaskInfo* task;
//    ~ExtendedTaskInfo()
//    {
//        for(int i = 0; i < childTasks.count(); i++)
//            delete childTasks[i];
//    }
//};

class TaskListModel : public QObject, ITaskListModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(IPluginModel ITaskListModel)

public:
    TaskListModel();
    ~TaskListModel();

private:
    // Native part
    QWidget* parent;
    QWidget* pluginWidget;

    QMap<IPluginModel*, MetaInfo*> childPlugins;
    QMap<IPluginView*, MetaInfo*> viewPlugins;
    IPluginView* activeView;

    // Unique part
    ITaskDataManagerPlugin* DBTool;
    ITaskListModel::TaskInfo* rootTask;

    // IPluginModel interface
public:
    virtual void AddChildPlugin(IPluginModel *, MetaInfo *);
    virtual void SetDataManager(QObject *);
    virtual void AddView(IPluginView *plugin, MetaInfo *meta);
    virtual bool Open(QWidget *parent);
    virtual bool Close();
    virtual QString GetError();  

    // ITaskListModel interface
public:
    TaskInfo *GetRootTask() override;
    void SetRootTask(TaskInfo* rootTask) override;
};

#endif // TASKLISTMODEL_H
