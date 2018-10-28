#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsCommon/plugin_base.h"

//! addtogroup UIManager_imp
//! {
class UIManager : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IPlugin
            )

public:
    UIManager();
    virtual ~UIManager() override;

    // PluginBase interface
public:
    virtual bool addReferencePlugin(const IPlugin *referencePlugin) override;
};
//! }
#endif // UIMANAGER_H
