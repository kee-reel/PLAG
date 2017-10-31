#ifndef EXPERIMENTCONTROLVIEW_H
#define EXPERIMENTCONTROLVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>

#include <QtCharts>

namespace Ui
{
class Form;
}


#include "iexperimentcontrolview.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views
#include "../../Models/ExperimentControlModel/iexperimentcontrolmodel.h"

//! addtogroup ExperimentControlView_imp
//! {
class ExperimentControlView : public
    QWidget,
    IExperimentControlView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IViewPlugin
        IExperimentControlView
    )

public:
    explicit ExperimentControlView(QWidget *parent = 0);
    ~ExperimentControlView();

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

    // IViewPlugin interface
public slots:
    bool Open(IModelPlugin *model) override;
    bool Close() override;

signals:
    void OnOpen(QWidget *);

private:
    PluginInfo *pluginInfo;

    IExperimentControlModel *myReferencedPlugin;

private:
    // Write your internal methods here
    Ui::Form *ui;
    QChart dataChart;
};
//! }
#endif // EXPERIMENTCONTROLVIEW_H
