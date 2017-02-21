#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../../System/MASS/interfaces.h"
#include "../../System/TaskDBToolPlugin/itaskdbtoolplugin.h"

template <class A>
class QVector;
class ITaskListModel : public IPluginModel
{
public:
    class TaskInfo{
    public:
        int id;
        QString name;
        TaskInfo* parent;
        QList<TaskInfo*> childTasks;
    };
    /// Get all data
    virtual TaskInfo* GetRootTask() = 0;
    /// Add new task
    virtual bool AddTask(TaskInfo* taskParent, TaskInfo newTask) = 0;
    /// Set new task data
    virtual bool EditTask(TaskInfo* task, TaskInfo newTaskData) = 0;
    /// Delete selected task
    virtual bool DeleteTask(TaskInfo* task) = 0;
};
Q_DECLARE_INTERFACE(ITaskListModel, "ITaskListModel v0.1")

#endif // ITASKLISTMODEL_H
