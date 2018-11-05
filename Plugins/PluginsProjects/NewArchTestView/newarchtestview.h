#ifndef NEWARCHTESTVIEW_H
#define NEWARCHTESTVIEW_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsCommon/plugin_base.h"

//! addtogroup NewArchTestView_imp
//! {
class NewArchTestView :
    public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
    )
public:
    NewArchTestView();
    virtual ~NewArchTestView() override;
};
//! }
#endif // NEWARCHTESTVIEW_H
