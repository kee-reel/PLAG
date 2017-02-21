#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../../System/MASS/interfaces.h"

template <class T>
class QList;
class ITaskDataManagerPlugin : public IDataManagerPlugin
{
public:
    class TaskInfo{
    public:
        int id;
        QString name;
        //int level;
        int parent;
        int position;
    };
    virtual QList<TaskInfo> GetTaskTree(QString treeName) = 0;
    virtual int AddTask(QString treeName, TaskInfo task) = 0;
    virtual bool EditTask(QString treeName, TaskInfo task) = 0;
    virtual bool DeleteTask(QString treeName, int id) = 0;
};
Q_DECLARE_INTERFACE(ITaskDataManagerPlugin, "ITaskDataManagerPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
