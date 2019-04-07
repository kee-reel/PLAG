#ifndef MODBUSDEVICEDATAMANAGER_H
#define MODBUSDEVICEDATAMANAGER_H

#include <QtCore>
#include <QDebug>
#include <QString>
#include <QModbusReply>
#include <QModbusClient>
#include <QSignalMapper>
#include <QtGui>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/imodbusdevicedatamanager.h"
#include "../../Interfaces/icomportdatamanager.h"

#include "modbusdevicehandler.h"

//! \addtogroup ModbusDeviceDataManager_imp
//!  \{
class ModbusDeviceDataManager : public
    PluginBase,
    IModbusDeviceDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        IModbusDeviceDataManager
    )

public:
    ModbusDeviceDataManager();
    virtual ~ModbusDeviceDataManager() override;

    // PluginBase interface
public:
    virtual void onAllReferencesSet() override;

    // IModbusDeviceDataManager interface
public:
    QList<PortInfo> GetAvailablePorts() override;
    bool OpenPort(QString portName, ConnectionSettings connectionSettings) override;
    void ScanForDevice(int deviceId) override;
    QList<IModbusDeviceHandler*> GetAvailableModbusDeviceHandlers() override;
    void ClosePort(QString portName) override;

signals:
    void ErrorOccurred(QString);
    void ModbusListUpdated();

private:
    ICOMPortDataManager *myReferencedPlugin;

private:
    // Write your internal methods here
    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;
    ICOMPortDataManager::ISerialPortHandler *connectedPort;
    QMap<int, ModbusDeviceHandler*> deviceHandlers;
    QStringListModel devicesNames;

    int scanningDeviceId;

    void CreateNewDevice(int deviceId);

private slots:
    void SendReadRequest(const QModbusDataUnit &dataUnit);
    void SendWriteRequest(const QModbusDataUnit &dataUnit);

    void OnDeviceConnectStateChanged();
    void ReadReady();

signals:
    void DataUnitRecieved(const QModbusDataUnit &dataUnit);
};
//!  \}
#endif // MODBUSDEVICEDATAMANAGER_H
