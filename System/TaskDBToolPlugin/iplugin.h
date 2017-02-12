#ifndef PLUGINSINTERFACES_H
#define PLUGINSINTERFACES_H

#include <QString>
#include <QWidget>

#include "pluginstructs.h"

class IPlugin
{
public:
    virtual QWidget* GetWidget() = 0;
    virtual void DoSomething() = 0;
    virtual void AddChildPlugin(IPlugin*, MetaInfo*) = 0;

    virtual bool Open() = 0;
    virtual bool Close() = 0;
    virtual QString GetError() = 0;
};
Q_DECLARE_INTERFACE(IPlugin, "TKPlugin v0.1")

#endif // PLUGINSINTERFACES_H
