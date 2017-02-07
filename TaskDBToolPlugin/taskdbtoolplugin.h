#ifndef TASKDBTOOLPLUGIN_H
#define TASKDBTOOLPLUGIN_H

#include "itaskdbtoolplugin.h"

class TaskDBToolPlugin : public QObject, ITaskDBManagerPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ITaskDBManagerPlugin" FILE "PluginMeta.json")
    Q_INTERFACES(ITaskDBManagerPlugin)

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
