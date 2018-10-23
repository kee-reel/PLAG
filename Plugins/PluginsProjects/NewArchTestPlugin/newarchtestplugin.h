#ifndef NEWARCHTESTPLUGIN_H
#define NEWARCHTESTPLUGIN_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsCommon/plugin_base.h"
#include "../../PluginsInterfaces/inewarchtestplugin.h"

//! addtogroup NewArchTestPlugin_imp
//! {
class NewArchTestPlugin : public
        PluginBase,
        INewArchTestPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IPlugin
            INewArchTestPlugin
            )

public:
    NewArchTestPlugin();
    virtual ~NewArchTestPlugin() override;

    // PluginBase interface
public:
    virtual bool addReferencePlugin(const IPlugin *referencePlugin) override;

    // INewArchTestPlugin interface
public:
    virtual int someMethod(int x) override;
};
//! }
#endif // NEWARCHTESTPLUGIN_H
