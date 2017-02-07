#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "idbtoolplugin.h"

class ITaskDBManagerPlugin : public IDBToolPlugin
{
    // IDBToolPlugin interface
public:
    virtual bool SetDBManager(IDBManagerPlugin *DBManager) = 0;

public:
    virtual bool CreateNewTask() = 0;
};
Q_DECLARE_INTERFACE(ITaskDBManagerPlugin, "ITaskDBManagerPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
