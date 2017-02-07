#ifndef IDBTOOLPLUGIN_H
#define IDBTOOLPLUGIN_H

#include "idbmanagerplugin.h"

class IDBToolPlugin
{
public:
    virtual bool SetDBManager(IDBManagerPlugin* DBManager) = 0;
};
Q_DECLARE_INTERFACE(IDBToolPlugin, "IDBToolPlugin v0.1")

#endif // IDBTOOLPLUGIN_H
