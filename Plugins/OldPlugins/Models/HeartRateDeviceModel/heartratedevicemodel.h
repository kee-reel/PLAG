#ifndef HEARTRATEDEVICEMODEL_H
#define HEARTRATEDEVICEMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "iheartratedevicemodel.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views

#include "../../Models/ExperimentControlModel/iexperimentcontrolmodel.h"
#include "../../Models/FuzzyLogicModel/ifuzzylogicmodel.h"

//! addtogroup HeartRateDeviceModel_imp
//! {
class HeartRateDeviceModel : public
    QObject,
    IHeartRateDeviceModel
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IModelPlugin
        IHeartRateDeviceModel
    )

public:
    HeartRateDeviceModel();
    ~HeartRateDeviceModel();

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

signals:
    void HeartbeatData(float);
    void TempoData(float);

private:
    PluginInfo *pluginInfo;

    IExperimentControlModel *deviceManager;
    IFuzzyLogicModel *fuzzyLogic;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    // Write your internal methods here
    QList<QLineSeries*> heartData;
    QLineSeries *HRData;
    QLineSeries *CO2Data;

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

    void InitSystems();
    void CompareValues(QPointF point);


    // IHeartRateDeviceModel interface
    void AddHeartbeat(QPointF point);
    
public:
    virtual void SetHbO2Data(float value) override;
};
//! }
#endif // HEARTRATEDEVICEMODEL_H
