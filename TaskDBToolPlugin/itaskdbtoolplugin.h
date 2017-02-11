#ifndef ITASKDBTOOLPLUGIN_H
#define ITASKDBTOOLPLUGIN_H

#include "../TimeKeeper/interfaces.h"

class ITaskDBToolPlugin : public IDBToolPlugin
{
public:
    virtual bool CreateNewTask() = 0;
};
Q_DECLARE_INTERFACE(ITaskDBToolPlugin, "ITaskDBToolPlugin v0.1")

#endif // ITASKDBTOOLPLUGIN_H
