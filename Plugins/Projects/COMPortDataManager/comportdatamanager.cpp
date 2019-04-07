#include "comportdatamanager.h"

COMPortDataManager::COMPortDataManager() :
    PluginBase()
{
    supportedDevices["ArduinoUno"] = DeviceInfo{9025, 67};
}

COMPortDataManager::~COMPortDataManager()
{

}

void COMPortDataManager::UpdateAvailablePorts()
{
    QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
    QList<QString> handledPortNames = portHandlers.keys();
    DeviceInfo deviceInfoBuf;
    qDebug() << "Connected ports count:" << availablePorts.length();

    foreach (auto port, availablePorts)
    {
        auto portName = port.portName();
        deviceInfoBuf.productId = port.productIdentifier();
        deviceInfoBuf.vendorId = port.vendorIdentifier();
        SerialPortHandler *portHandler;

        if(!portHandlers.contains(portName))
        {
            portHandler = new SerialPortHandler(portName, this);
            portHandlers.insert(portName, portHandler);
        }
        else
        {
            portHandler = portHandlers[portName];
        }

        bool isDeviceSupported = IsDeviceSupported(deviceInfoBuf);
        portHandler->SetIsSupported(isDeviceSupported);
        // Needs to find handlers which handles disconnected ports.
        handledPortNames.removeOne(portName);
    }

    if(handledPortNames.length() != 0)
    {
        foreach (auto portName, handledPortNames)
        {
            delete portHandlers[portName];
            portHandlers.remove(portName);
        }
    }
}

void COMPortDataManager::AddSupportedDevice(QString deviceName, ICOMPortDataManager::DeviceInfo &deviceInfo)
{
    if(!IsDeviceSupported(deviceInfo))
    {
        supportedDevices.insert(deviceName, deviceInfo);
    }
}

bool COMPortDataManager::IsDeviceSupported(ICOMPortDataManager::DeviceInfo &deviceInfo)
{
    auto deviceIter = supportedDevices.begin();

    while(deviceIter != supportedDevices.end())
    {
        if(CompareDeviceInfo(deviceIter.value(), deviceInfo))
        {
            return true;
        }

        ++deviceIter;
    }

    return false;
}

bool COMPortDataManager::CompareDeviceInfo(DeviceInfo device, DeviceInfo &deviceInfo)
{
    // I don't compare names because it could vary because of user, but Ids - don't
    return device.productId == deviceInfo.productId &&
           device.vendorId == deviceInfo.vendorId;
}

QMap<QString, ICOMPortDataManager::DeviceInfo> COMPortDataManager::GetSupportedDevices()
{
    return supportedDevices;
}

QMap<QString, ICOMPortDataManager::ISerialPortHandler *> COMPortDataManager::GetPortHandlers()
{
    UpdateAvailablePorts();
    QMap<QString, ICOMPortDataManager::ISerialPortHandler *> convertedMap;
    auto iter = portHandlers.begin();

    while(iter != portHandlers.end())
    {
        if(iter.value()->IsSupported())
            convertedMap.insert(iter.key(), (ICOMPortDataManager::ISerialPortHandler*)iter.value());

        ++iter;
    }

    return convertedMap;
}


void COMPortDataManager::onAllReferencesReady()
{
    UpdateAvailablePorts();
}
