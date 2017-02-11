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
    virtual bool CreateNewTask() override;

public:
    TaskDBToolPlugin();

private:
    IDBManagerPlugin* DBManager;


};

#endif // TASKDBTOOLPLUGIN_H
