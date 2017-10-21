#include "hardwaredatamanager.h"

#include <QSerialPortInfo>
#include <QList>
#include <QTimer>

HardwareDataManager::HardwareDataManager()
{
    /*
        ui->setupUi(this);
        */
}

HardwareDataManager::~HardwareDataManager()
{
    foreach (auto device, deviceDataHandlers)
    {
        delete device;
    }
}

void HardwareDataManager::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void HardwareDataManager::OnAllSetup()
{
    auto ports = myReferencedPlugin->GetPortHandlers();

    if(ports.count() == 0)
        return;

    auto iter = ports.begin();
    auto deviceDataHandler = new DeviceDataHandler(iter.value(), this);
    deviceDataHandlers.insert(iter.key(), deviceDataHandler);
    QTimer::singleShot(1000, [=]()
    {
        QByteArray buf = "o0";
        deviceDataHandler->WriteData(buf);
    });
    QTimer::singleShot(5000, [=]()
    {
        QByteArray buf = "o0";
        deviceDataHandler->WriteData(buf);
    });
}

QString HardwareDataManager::GetLastError()
{
}

void HardwareDataManager::AddReferencePlugin(PluginInfo *pluginInfo)
{
    // Select your plugin case and get it. For example:
    /*
        case PLUGINMODEL:{
            myReferencedPlugin = qobject_cast<ISomePlugin*>(pluginInfo->Instance);
            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ISomePlugin.";
                return;
            }
            qDebug() << "ISomePlugin succesfully set.";
            connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
        } break;
    */
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

        case DATASOURCE:
            {
                myReferencedPlugin = qobject_cast<ICOMPortDataSource*>(pluginInfo->Instance);

                if(!myReferencedPlugin)
                {
                    qDebug() << pluginInfo->Meta->Name << "is not ICOMPortDataSource.";
                    return;
                }

                qDebug() << "ICOMPortDataSource succesfully set.";
                connect(this, SIGNAL(OnClose(PluginInfo*)), pluginInfo->Instance, SLOT(ReferencePluginClosed(PluginInfo*)));
                SetupDataSource();
            } break;
    }
}

void HardwareDataManager::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

void HardwareDataManager::SetupDataSource()
{
    ICOMPortDataSource::DeviceInfo ArduinoUnoDevice = {9025, 67};
    //    auto supportedDevices = myReferencedPlugin->GetSupportedDevices();
    //    if(!supportedDevices.contains("ArduinoUno"))
    //    {
    //        myReferencedPlugin->AddSupportedDevice("ArduinoUno", ArduinoUnoDevice);
    //        myReferencedPlugin->UpdatePortsList();
    //    }
    //    auto availableSupportedPorts = myReferencedPlugin->GetAvailableSupportedPorts();
    //    QSerialPortInfo arduinoPort;
    //    foreach (auto port, availableSupportedPorts)
    //    {
    //        if(port.vendorIdentifier() == ArduinoUnoDevice.vendorId &&
    //                port.productIdentifier() == ArduinoUnoDevice.productId)
    //        {
    //            arduinoPort = port;
    //            break;
    //        }
    //    }
    //    if(arduinoPort.isNull())
    //    {
    //        qDebug() << "Can't connect to device port";
    //        return;
    //    }
}


