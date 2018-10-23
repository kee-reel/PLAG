#ifndef EXPERIMENTCONTROLMODEL_H
#define EXPERIMENTCONTROLMODEL_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QDateTime>

#include "iexperimentcontrolmodel.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views

#include "../../DataManagers/ModbusDeviceDataManager/imodbusdevicedatamanager.h"

#include "modbusdevicesmodel.h"
#include "registerspacktablemodel.h"

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

    Q_PROPERTY(bool ExperimentState MEMBER experimentState NOTIFY ExperimentStateChanged)

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

    // IExperimentControlModel interface
public:
    //    QList<IExperimentSetup *> GetAvailableExperimentSetups() override;
    void StartExperiment() override;
    void StopExperiment() override;

    // IExperimentControlModel interface
public:
    QAbstractItemModel *GetRegisterPacks() override;
    void AddRegisterPack(RegstersPack pack) override;
    void SetDeviceForSetup(QString deviceName) override;

    QList<QLineSeries *> GetRegistersLineSeries() override;

    QAbstractItemModel *GetAvailablePorts() override;
    void UpdateAvailablePorts() override;
    bool OpenPort(int modelIndex, IModbusDeviceDataManager::ConnectionSettings connectionSettings) override;
    void ScanForDevice(int deviceId) override;
    QAbstractItemModel *GetAvailableModbusDeviceHandlers() override;
    QAbstractItemModel *GetAvailableModbusDeviceNames() override;
    void ClosePort(int modelIndex) override;

signals:
    void ErrorOccurred(QString error);
    void ExperimentStateChanged(bool state);

private:
    PluginInfo *pluginInfo;

    PluginInfo *openedModel;
    QList< PluginInfo* > relatedModelPlugins;
    PluginInfo *openedView;
    QList< PluginInfo* > relatedViewPlugins;

private:
    IModbusDeviceDataManager *myReferencedPlugin;
    QtCharts::QLineSeries lineSerie;
    QTime dataRecieveTime;
    bool experimentState;
    QDateTime experimentStartTime;
    //    QList<IExperimentSetup *> experimentSetups;
    QList<IModbusDeviceDataManager::IModbusDeviceHandler*> deviceHandlers;

    QStandardItemModel AvailablePortsModel;
    ModbusDevicesModel AvailableDevicesModel;
    RegistersPackTableModel RegisterPacksModel;

private slots:
    void ProcessDataInput(QModbusDataUnit::RegisterType dataType, const QVector<quint16> &data);
    void UpdateDevicesList();

    // IExperimentControlModel interface
public:
    virtual bool GetExperimentState() override;
    virtual QDateTime GetExperimentStartTime() override;
    virtual bool SaveExperimentData(QString filename) override;
};
//! }
#endif // EXPERIMENTCONTROLMODEL_H
