#ifndef HEARTRATEDEVICEVIEW_H
#define HEARTRATEDEVICEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QString>

#include "../../Common/plugin_base.h"
#include "../../Interfaces/iheartratedevice.h"

//! \addtogroup HeartRateDevice_imp
//!  \{
class HeartRateDeviceView : public PluginBase
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
    )

public:
    explicit HeartRateDeviceView(QWidget *parent = nullptr);
    virtual ~HeartRateDeviceView() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

private slots:
    void OnHeartbitData(float data);
    void OnTempoData(float data);

    void on_buttonStart_clicked();
    void on_buttonStop_clicked();
    void on_buttonClose_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_spinDataIndex_valueChanged(int position);

private:
    IHeartRateDevice *myReferencedPlugin;
    int dataIndex;

};
//!  \}
#endif // HEARTRATEDEVICEVIEW_H
