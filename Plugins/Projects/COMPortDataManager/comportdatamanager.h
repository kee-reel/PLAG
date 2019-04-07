#ifndef COMPortDataManager_H
#define COMPortDataManager_H

#include <QtCore>
#include <QDebug>
#include <QString>
#include <QList>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDateTime>

#include "../../Common/plugin_base.h"

#include "../../Interfaces/icomportdatamanager.h"
#include "serialporthandler.h"

//! \addtogroup COMPortDataManager_imp
//!  \{
class COMPortDataManager : public PluginBase, ICOMPortDataManager
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "TimeKeeper.Module.Test" FILE "PluginMeta.json")
    Q_INTERFACES(
        IPlugin
        ICOMPortDataManager
    )

public:
    COMPortDataManager();
    virtual ~COMPortDataManager() override;

private: // Internal methods and fields:
    QMap<QString, SerialPortHandler*> portHandlers;
    QMap<QString, DeviceInfo> supportedDevices;

    bool CompareDeviceInfo(DeviceInfo device, ICOMPortDataManager::DeviceInfo &deviceInfo);
    bool IsDeviceSupported(ICOMPortDataManager::DeviceInfo &deviceInfo);

    // ICOMPortDataManager interface
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
//!  \}
#endif // COMPortDataManager_H
