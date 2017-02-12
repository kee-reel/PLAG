#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include <QString>
#include <QtSql>

#include "itaskdbtoolplugin.h"

class TaskDBToolPlugin : public QObject, ITaskDBToolPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TaskDBToolPlugin" FILE "PluginMeta.json")
    Q_INTERFACES(IDBToolPlugin ITaskDBToolPlugin)

    // ITaskDBManagerPlugin interface
public:
    virtual bool SetDBManager(IDBManagerPlugin *DBManager) override;
    virtual QString GetError();

    // ITaskDBToolPlugin interface
public:
    virtual TaskInfo *GetTaskTree(QString treeName);
    virtual bool AddTask(TaskInfo *taskTree);
    virtual bool EditTask(TaskInfo *taskTree);
    virtual bool DeleteTask(TaskInfo *taskTree);

public:
    TaskDBToolPlugin();
    ~TaskDBToolPlugin();

private:
    IDBManagerPlugin* DBManager;
    QMap<QString, QString> tableStruct;

    bool IsTableExists(QString tableName);
    bool IsTableRightStructure(QString tableName);
    QString GetStringStruct();
};

#endif // TASKDBTOOLPLUGIN_H
