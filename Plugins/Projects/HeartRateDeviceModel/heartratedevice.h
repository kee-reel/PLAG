#ifndef HeartRateDevice_H
#define HeartRateDevice_H

#include <QtCore>
#include <QDebug>
#include <QString>
#include <QLineSeries>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/iheartratedevice.h"
#include "../../Interfaces/imodbusdatareader.h"
#include "../../Interfaces/ifuzzylogicmanager.h"

//! \addtogroup HeartRateDevice_imp
//! \{
class HeartRateDevice : public
    PluginBase,
    IHeartRateDevice
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IHeartRateDevice
    )

public:
    HeartRateDevice();
    virtual ~HeartRateDevice() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;
    virtual void onAllReferencesReady() override;

signals:
    void HeartbeatData(float);
    void TempoData(float);

private:
    IModbusDataReader *deviceManager;
    IFuzzyLogicManager *fuzzyLogic;

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

    IFuzzyLogicManager::IInputVariable *fuzzyHR;
    IFuzzyLogicManager::IInputVariable *fuzzyCO2;
    IFuzzyLogicManager::IOutputVariable *fuzzyTempo;

    IFuzzyLogicManager::IFuzzySet *lowHRSet;
    IFuzzyLogicManager::IFuzzySet *medHRSet;
    IFuzzyLogicManager::IFuzzySet *highHRSet;

    IFuzzyLogicManager::IFuzzySet *lowCO2Set;
    IFuzzyLogicManager::IFuzzySet *medCO2Set;
    IFuzzyLogicManager::IFuzzySet *highCO2Set;

    IFuzzyLogicManager::IFuzzySet *lowTempoSet;
    IFuzzyLogicManager::IFuzzySet *medTempoSet;
    IFuzzyLogicManager::IFuzzySet *highTempoSet;


private slots:
    void CompareValues(int index);


    // IHeartRateDevice interface
public slots:
    virtual void SetHbO2Data(float value) override;
    virtual void ChooseDataIndex(int index) override;
    virtual void StartTracking() override;
    virtual void StopTracking() override;

    void AddHeartbeat(QPointF point);
};
//! \}
#endif // HeartRateDevice_H
