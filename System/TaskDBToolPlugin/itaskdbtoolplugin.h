#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../../System/TimeKeeper/interfaces.h"

template <class T>
class QList;
class ITaskDBToolPlugin : public IDBToolPlugin
{
public:
    class TaskInfo{
    public:
        int id;
        QString name;
        int level;
        int parent;
        int position;
        QList<TaskInfo*> childTasks;
    };
    virtual TaskInfo *GetTaskTree(QString treeName) = 0;
    virtual bool AddTask(TaskInfo* taskTree) = 0;
    virtual bool EditTask(TaskInfo* taskTree) = 0;
    virtual bool DeleteTask(TaskInfo* taskTree) = 0;
};
Q_DECLARE_INTERFACE(ITaskDBToolPlugin, "ITaskDBToolPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
