#ifndef HEARTRATEDEVICEMODEL_H
#define HEARTRATEDEVICEMODEL_H

#include <QtCore>
#include <QDebug>
#include <QString>
#include <QLineSeries>

#include "../../PluginsCommon/plugin_base.h"

#include "../../PluginsInterfaces/iheartratedevicemodel.h"
#include "../../PluginsInterfaces/iexperimentcontrolmodel.h"
#include "../../PluginsInterfaces/ifuzzylogicmodel.h"

//! addtogroup HeartRateDeviceModel_imp
//! {
class HeartRateDeviceModel : public
    PluginBase,
    IHeartRateDeviceModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IHeartRateDeviceModel
    )

public:
    HeartRateDeviceModel();
    virtual ~HeartRateDeviceModel() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

signals:
    void HeartbeatData(float);
    void TempoData(float);

private:
    IExperimentControlModel *deviceManager;
    IFuzzyLogicModel *fuzzyLogic;

    // Write your internal methods here
    QList<QLineSeries*> heartData;
    QLineSeries *HRData;
    QLineSeries *CO2Data;

    int heartRateDataIndex;
    QLinkedList<float> beatsList;
    int savedBeatsCount;
    bool isFalling;
    float minLowerValue;
    float maxLowerValue;
    float heartRate;

    IFuzzyLogicModel::IInputVariable *fuzzyHR;
    IFuzzyLogicModel::IInputVariable *fuzzyCO2;
    IFuzzyLogicModel::IOutputVariable *fuzzyTempo;

    IFuzzyLogicModel::IFuzzySet *lowHRSet;
    IFuzzyLogicModel::IFuzzySet *medHRSet;
    IFuzzyLogicModel::IFuzzySet *highHRSet;

    IFuzzyLogicModel::IFuzzySet *lowCO2Set;
    IFuzzyLogicModel::IFuzzySet *medCO2Set;
    IFuzzyLogicModel::IFuzzySet *highCO2Set;

    IFuzzyLogicModel::IFuzzySet *lowTempoSet;
    IFuzzyLogicModel::IFuzzySet *medTempoSet;
    IFuzzyLogicModel::IFuzzySet *highTempoSet;


private slots:
    void CompareValues(int index);


    // IHeartRateDeviceModel interface
public slots:
    virtual void SetHbO2Data(float value) override;
    virtual void ChooseDataIndex(int index) override;
    virtual void StartTracking() override;
    virtual void StopTracking() override;

    void AddHeartbeat(QPointF point);
};
//! }
#endif // HEARTRATEDEVICEMODEL_H
