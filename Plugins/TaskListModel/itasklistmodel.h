#ifndef ITASKLISTMODEL_H
#define ITASKLISTMODEL_H

#include "../../System/TimeKeeper/interfaces.h"

template <class T>
class QList;
class ITaskListModel : public IPluginModel
{
public:
    class TaskInfo{
    public:
        virtual ~TaskInfo();
        QString task;
        QList<TaskInfo*> childTasks;
    };

    virtual TaskInfo* GetRootTask() = 0;
    virtual void SetRootTask(TaskInfo* rootTask) = 0;
};
Q_DECLARE_INTERFACE(ITaskListModel, "ITaskListModel v0.1")

#endif // ITASKLISTMODEL_H
