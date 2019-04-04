#ifndef TIMERMODEL_H
#define TIMERMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "../../PluginsCommon/plugin_base.h"

#include "../../PluginsInterfaces/itimermodel.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views


//! addtogroup TimerModel_imp
//! {
class TimerModel : public
        PluginBase,
        ITimerModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IPlugin
            ITimerModel
            )

public:
    TimerModel();
    virtual ~TimerModel() override;


private:
    // Write your internal methods here
};
//! }
#endif // TIMERMODEL_H
