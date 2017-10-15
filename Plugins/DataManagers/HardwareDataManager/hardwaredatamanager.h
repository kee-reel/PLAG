#ifndef HARDWAREDATAMANAGER_H
#define HARDWAREDATAMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "ihardwaredatamanager.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views


//! addtogroup HardwareDataManager_imp
//! {
class HardwareDataManager : public
        QObject,
        IHardwareDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IDataManagerPlugin
            IHardwareDataManager
            )

public:
    HardwareDataManager();
    ~HardwareDataManager();

    // IPlugin interface
public:
    void SetPluginInfo(PluginInfo *pluginInfo) override;
    void OnAllSetup() override;
    QString GetLastError() override;
    void AddReferencePlugin(PluginInfo *pluginInfo) override;

public slots:
    void ReferencePluginClosed(PluginInfo *pluginInfo) override;

signals:
    void OnClose(PluginInfo*);
    void OnClose();



private:
    PluginInfo *pluginInfo;

    // ISomePlugin *myReferencedPlugin;


private:
    // Write your internal methods here
};
//! }
#endif // HARDWAREDATAMANAGER_H
