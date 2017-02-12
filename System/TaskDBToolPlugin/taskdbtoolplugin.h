#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QString>
#include <QtSql>
#include <QObject>

#include "itaskdbtoolplugin.h"

class TaskDataManagerPlugin : public QObject, ITaskDataManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TaskDBToolPlugin" FILE "PluginMeta.json")
    Q_INTERFACES(IDataManagerPlugin ITaskDataManagerPlugin)

    // IDataManagerPlugin interface
public:
    virtual bool SetDataSource(QObject *dataSource);
    virtual QString GetError();

    // ITaskDBToolPlugin interface
public:
    virtual TaskInfo *GetTaskTree(QString treeName);
    virtual bool AddTask(TaskInfo *taskTree);
    virtual bool EditTask(TaskInfo *taskTree);
    virtual bool DeleteTask(TaskInfo *taskTree);

public:
    TaskDataManagerPlugin();
    ~TaskDataManagerPlugin();

private:
    IDataBaseSourcePlugin* dataSource;
    QMap<QString, QString> tableStruct;

    bool IsTableExists(QString tableName);
    bool IsTableRightStructure(QString tableName);
    QString GetStringStruct();

};

#endif // TASKDBTOOLPLUGIN_H
