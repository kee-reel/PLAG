#ifndef TIMERMODEL_H
#define TIMERMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "itimermodel.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views


//! addtogroup TimerModel_imp
//! {
class TimerModel : public
        QObject,
        ITimerModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IModelPlugin
            ITimerModel
            )

public:
    TimerModel();
    ~TimerModel();

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

    // IModelPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    void Close() override;


private:
    PluginInfo *pluginInfo;

    // ISomePlugin *myReferencedPlugin;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    // Write your internal methods here
};
//! }
#endif // TIMERMODEL_H
