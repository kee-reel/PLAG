#ifndef PLUGINSINTERFACES_H
#define PLUGINSINTERFACES_H

#include <QString>
#include <QWidget>

#include "pluginstructs.h"

class IPluginModel
{
public:
    virtual void DoSomething() = 0;
    virtual void AddChildPlugin(IPluginModel*, MetaInfo*) = 0;
    virtual void AddDBTool(QObject*) = 0;

    virtual bool Open(QWidget*) = 0;
    virtual bool Close() = 0;
    virtual QString GetError() = 0;
};
Q_DECLARE_INTERFACE(IPluginModel, "IModelPlugin v0.1")

#endif // PLUGINSINTERFACES_H
