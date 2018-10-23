#ifndef COMPORTDATASOURCE_H
#define COMPORTDATASOURCE_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDateTime>

#include "icomportdatasource.h"
#include "serialporthandler.h"

// Here you can include your related plugins interfaces
// For example: #include "../../Models/SomeModel/isomemodel.h"

//! addtogroup COMPortDataSource_imp
//! {
class COMPortDataSource : public QObject, ICOMPortDataSource
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IDataSourcePlugin
        ICOMPortDataSource
    )

public:
    COMPortDataSource();
    ~COMPortDataSource();

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

    // IDataSourcePlugin interface
public:
    ///!
    //! \brief UpdatePortsList
    //! Update available and supported ports.
    //!
    void Setup() override;

private:
    PluginInfo *pluginInfo;

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
};
//! }
#endif // COMPORTDATASOURCE_H
