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

private slots:
    void on_connectButton_clicked();
    void on_scanButton_clicked();
    void on_refreshButton_clicked();
    void on_addRegisterPackButton_clicked();
    void on_removeRegistersButton_clicked();
    void on_deviceNamesCombo_currentIndexChanged(const QString &arg1);

    void on_buttonStart_clicked();

    void on_chartScroll_sliderMoved(int position);

    void SeriesPointAdded(int index);

private:
    PluginInfo *pluginInfo;

    IExperimentControlModel *myReferencedPlugin;

private:
    // Write your internal methods here
    Ui::Form *ui;
    QChart dataChart;
    void SetupData();
    void RemoveModelItem(QAbstractItemView *view);
    int previousSliderValue;
    int currentChartXScale;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
//! }
#endif // EXPERIMENTCONTROLVIEW_H
