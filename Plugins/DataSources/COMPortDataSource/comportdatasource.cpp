#include "comportdatasource.h"

COMPortDataSource::COMPortDataSource()
{
    supportedDevices["ArduinoUno"] = DeviceInfo{9025, 67};
    Setup();
}

COMPortDataSource::~COMPortDataSource()
{
    foreach (auto port, portHandlers)
    {
        if(port->isOpen())
            port->clear();

        delete port;
    }
}

void COMPortDataSource::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void COMPortDataSource::OnAllSetup()
{
    Setup();
}

QString COMPortDataSource::GetLastError()
{
}

void COMPortDataSource::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case PLUGINVIEW:
            {
            } break;

        case PLUGINMODEL:
            {
            } break;

        case ROOTMODEL:
            {
            } break;

        case DATAMANAGER:
            {
            } break;
    }
}

void COMPortDataSource::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

void COMPortDataSource::Setup()
{
    UpdateAvailablePorts();
}

void COMPortDataSource::UpdateAvailablePorts()
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

void COMPortDataSource::AddSupportedDevice(QString deviceName, ICOMPortDataSource::DeviceInfo &deviceInfo)
{
    if(!IsDeviceSupported(deviceInfo))
    {
        supportedDevices.insert(deviceName, deviceInfo);
    }
}

bool COMPortDataSource::IsDeviceSupported(ICOMPortDataSource::DeviceInfo &deviceInfo)
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

bool COMPortDataSource::CompareDeviceInfo(DeviceInfo device, DeviceInfo &deviceInfo)
{
    // I don't compare names because it could vary because of user, but Ids - don't
    return device.productId == deviceInfo.productId &&
           device.vendorId == deviceInfo.vendorId;
}

QMap<QString, ICOMPortDataSource::DeviceInfo> COMPortDataSource::GetSupportedDevices()
{
    return supportedDevices;
}

QMap<QString, ICOMPortDataSource::ISerialPortHandler *> COMPortDataSource::GetPortHandlers()
{
    UpdateAvailablePorts();
    QMap<QString, ICOMPortDataSource::ISerialPortHandler *> convertedMap;
    auto iter = portHandlers.begin();

    while(iter != portHandlers.end())
    {
        if(iter.value()->IsSupported())
            convertedMap.insert(iter.key(), (ICOMPortDataSource::ISerialPortHandler*)iter.value());

        ++iter;
    }

    return convertedMap;
}
