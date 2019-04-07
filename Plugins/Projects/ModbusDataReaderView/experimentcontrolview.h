#ifndef EXPERIMENTCONTROLVIEW_H
#define EXPERIMENTCONTROLVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>

#include <QtCharts>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/imodbusdatareader.h"

//! \addtogroup ModbusDataReader_dep
//!  \{
class ModbusDataReaderView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
    )

public:
    explicit ModbusDataReaderView(QWidget *parent = 0);
    virtual ~ModbusDataReaderView() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private slots:
    void on_closeButton_clicked();
    void on_connectButton_clicked();
    void on_scanButton_clicked();
    void on_refreshButton_clicked();
    void on_addRegisterPackButton_clicked();
    void on_removeRegistersButton_clicked();
    void on_deviceNamesCombo_currentIndexChanged(const QString &arg1);
    void on_buttonStart_clicked();
    void on_chartScroll_sliderMoved(int position);
    void SeriesPointAdded(QLineSeries *line, int index);
    void on_buttonRunExperiment_clicked();
    void onExperimentStateChanged(bool state);
    void on_buttonSaveResults_clicked();
    void on_buttonFilenameDialog_clicked();

private:
    void SetDataFilename(QString filename = "");
    void SetupData();
    void RemoveModelItem(QAbstractItemView *view);

private:
    IModbusDataReader *myReferencedPlugin;
    QChart dataChart;
    int previousSliderValue;
    int currentChartXScale;
    float minYValue;
    float maxYValue;
//    QTimer clockUpdateTimer;
    QTime timeSinceStartPassed;

public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
//!  \}
#endif // EXPERIMENTCONTROLVIEW_H
