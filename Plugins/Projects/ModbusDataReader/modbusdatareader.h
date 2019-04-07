#ifndef ModbusDataReaderModel_H
#define ModbusDataReaderModel_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QTimer>
#include <QDateTime>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/imodbusdatareader.h"
#include "../../Interfaces/imodbusdevicedatamanager.h"

#include "modbusdevicesmodel.h"
#include "registerspacktablemodel.h"

//! \addtogroup ModbusDataReader_imp
//! \{
class ModbusDataReader : public
    PluginBase,
    IModbusDataReader
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IModbusDataReader
    )

    Q_PROPERTY(bool ExperimentState MEMBER experimentState NOTIFY ExperimentStateChanged)

public:
    ModbusDataReader();
    virtual ~ModbusDataReader() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;

    // IModbusDataReader interface
public:
    //    QList<IExperimentSetup *> GetAvailableExperimentSetups() override;
    void StartReading() override;
    void StopReading() override;

    // IModbusDataReader interface
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

    // IModbusDataReader interface
public:
    virtual bool GetReadingState() override;
    virtual QDateTime GetReadingStartTime() override;
    virtual bool SaveReadingData(QString filename) override;
};
//! \}
#endif // ModbusDataReaderModel_H
