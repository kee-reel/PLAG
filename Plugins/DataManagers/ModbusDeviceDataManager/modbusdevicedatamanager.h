#ifndef MODBUSDEVICEDATAMANAGER_H
#define MODBUSDEVICEDATAMANAGER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QModbusReply>
#include <QModbusClient>
#include <QSignalMapper>
#include <QtGui>

#include "imodbusdevicedatamanager.h"
#include "modbusdevicehandler.h"

// Here you can include your related plugins interfaces
// For example:
// #include "../../[PluginTypes]/SomePlugin/isomeplugin.h"
// [Plugin types]: DataSources, DataManagers, Models, Views
#include "../../DataSources/COMPortDataSource/icomportdatasource.h"

//! addtogroup ModbusDeviceDataManager_imp
//! {
class ModbusDeviceDataManager : public
    QObject,
    IModbusDeviceDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IDataManagerPlugin
        IModbusDeviceDataManager
    )

public:
    ModbusDeviceDataManager();
    ~ModbusDeviceDataManager();

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
    PluginInfo *pluginInfo;
    ICOMPortDataSource *myReferencedPlugin;

private:
    // Write your internal methods here
    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;
    ICOMPortDataSource::ISerialPortHandler *connectedPort;
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
//! }
#endif // MODBUSDEVICEDATAMANAGER_H
