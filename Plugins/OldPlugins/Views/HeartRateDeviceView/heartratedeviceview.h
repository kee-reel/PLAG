#ifndef HEARTRATEDEVICEVIEW_H
#define HEARTRATEDEVICEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>

namespace Ui
{
class Form;
}

#include "iheartratedeviceview.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views

#include "../../Models/HeartRateDeviceModel/iheartratedevicemodel.h"

//! addtogroup HeartRateDeviceView_imp
//! {
class HeartRateDeviceView : public
    QWidget,
    IHeartRateDeviceView
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IViewPlugin
        IHeartRateDeviceView
    )

public:
    explicit HeartRateDeviceView(QWidget *parent = 0);
    ~HeartRateDeviceView();

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


private slots:
    void on_pushButton_clicked();
    void OnHeartbitData(float data);
    void OnTempoData(float data);

    void on_horizontalSlider_sliderMoved(int position);

private:
    PluginInfo *pluginInfo;

    IHeartRateDeviceModel *myReferencedPlugin;


private:
    // Write your internal methods here
    Ui::Form *ui;
};
//! }
#endif // HEARTRATEDEVICEVIEW_H
