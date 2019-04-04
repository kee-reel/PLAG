#ifndef COMPORTDATASOURCE_H
#define COMPORTDATASOURCE_H

#include <QtCore>
#include <QDebug>
#include <QString>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDateTime>

#include "../../PluginsCommon/plugin_base.h"

#include "../../PluginsInterfaces/icomportdatasource.h"
#include "serialporthandler.h"

// Here you can include your related plugins interfaces
// For example: #include "../../Models/SomeModel/isomemodel.h"

//! addtogroup COMPortDataSource_imp
//! {
class COMPortDataSource : public PluginBase, ICOMPortDataSource
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        ICOMPortDataSource
    )

public:
    COMPortDataSource();
    virtual ~COMPortDataSource() override;

private: // Internal methods and fields:
    QMap<QString, SerialPortHandler*> portHandlers;
    QMap<QString, DeviceInfo> supportedDevices;

    bool CompareDeviceInfo(DeviceInfo device, ICOMPortDataSource::DeviceInfo &deviceInfo);
    bool IsDeviceSupported(ICOMPortDataSource::DeviceInfo &deviceInfo);

    // ICOMPortDataSource interface
    void UpdateAvailablePorts();

public:
    void AddSupportedDevice(QString deviceName, DeviceInfo &deviceInfo) override;
    QMap<QString, DeviceInfo> GetSupportedDevices() override;
    QMap<QString, ISerialPortHandler *> GetPortHandlers() override;

signals:
    void OnNewInput(QByteArray *buffer);

    // PluginBase interface
protected:
    virtual void onAllReferencesReady() override;
};
//! }
#endif // COMPORTDATASOURCE_H
