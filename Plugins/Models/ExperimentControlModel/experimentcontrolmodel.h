#ifndef EXPERIMENTCONTROLMODEL_H
#define EXPERIMENTCONTROLMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "iexperimentcontrolmodel.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views


//! addtogroup ExperimentControlModel_imp
//! {
class ExperimentControlModel : public
        QObject,
        IExperimentControlModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
            IModelPlugin
            IExperimentControlModel
            )

public:
    ExperimentControlModel();
    ~ExperimentControlModel();

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
#endif // EXPERIMENTCONTROLMODEL_H
