#include "modbusdevicedatamanager.h"

#include <QModbusRtuSerialMaster>
#include <QDebug>
#include <QTimer>
#include <qserialportinfo.h>

ModbusDeviceDataManager::ModbusDeviceDataManager()
{
    modbusDevice = NULL;
    lastRequest = NULL;
    connect(this, &ModbusDeviceDataManager::ErrorOccurred, [](QString error)
    {
        qDebug() << "Modbus error:" << error;
    });
}

ModbusDeviceDataManager::~ModbusDeviceDataManager()
{
    foreach (auto device, deviceHandlers)
    {
        delete device;
    }

    deviceHandlers.clear();
}

void ModbusDeviceDataManager::SetPluginInfo(PluginInfo *pluginInfo)
{
    this->pluginInfo = pluginInfo;
}

void ModbusDeviceDataManager::OnAllSetup()
{
}


void ModbusDeviceDataManager::ScanPortForDevices(int deviceId)
{
    isScanPortForDevicesEnded = false;
    auto serviceUnit = QModbusDataUnit(QModbusDataUnit::InputRegisters, 50, 4);
    scanningDeviceId = deviceId;
    SendReadRequest(serviceUnit);
}

QString ModbusDeviceDataManager::GetLastError()
{
}

void ModbusDeviceDataManager::AddReferencePlugin(PluginInfo *pluginInfo)
{
    switch(pluginInfo->Meta->Type)
    {
        case DATASOURCE:
        {
            myReferencedPlugin = qobject_cast<ICOMPortDataSource*>(pluginInfo->Instance);

            if(!myReferencedPlugin)
            {
                qDebug() << pluginInfo->Meta->Name << "is not ICOMPortDataSource.";
                return;
            }

            qDebug() << "ICOMPortDataSource succesfully set.";
        }
    }
}

void ModbusDeviceDataManager::ReferencePluginClosed(PluginInfo *pluginInfo)
{
}

QList<IModbusDeviceDataManager::PortInfo> ModbusDeviceDataManager::GetAvailablePorts()
{
    auto portHandlers = myReferencedPlugin->GetPortHandlers();
    QList<IModbusDeviceDataManager::PortInfo> availablePorts;
    IModbusDeviceDataManager::PortInfo portInfo;

    foreach (auto portHandler, portHandlers)
    {
        QSerialPortInfo port = QSerialPortInfo(*portHandler->GetSerialPort());
        portInfo.portName = port.portName();
        portInfo.productId = port.productIdentifier();
        portInfo.vendorId = port.vendorIdentifier();
        availablePorts.append(portInfo);
    }

    return availablePorts;
}

bool ModbusDeviceDataManager::OpenPort(QString portName, IModbusDeviceDataManager::ConnectionSettings connectionSettings)
{
    if (modbusDevice)
    {
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        modbusDevice = nullptr;
    }

    modbusDevice = new QModbusRtuSerialMaster(this);
    connect(modbusDevice, &QModbusClient::errorOccurred, [this](QModbusDevice::Error)
    {
        emit ErrorOccurred(modbusDevice->errorString());
    });

    if (!modbusDevice)
    {
        qDebug() << "Could not create Modbus master.";
    }
    else
    {
        connect(modbusDevice, &QModbusClient::stateChanged,
                this, &ModbusDeviceDataManager::OnDeviceConnectStateChanged);
    }

    if (modbusDevice->state() != QModbusDevice::ConnectedState)
    {
        modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                                             portName);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                                             connectionSettings.parity);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                                             connectionSettings.baud);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                                             connectionSettings.dataBits);
        modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                                             connectionSettings.stopBits);
        modbusDevice->setTimeout(connectionSettings.responseTimeout);
        modbusDevice->setNumberOfRetries(connectionSettings.numberOfRetries);

        if (!modbusDevice->connectDevice())
        {
            qDebug() << "Connect failed: " << modbusDevice->errorString();
        }
    }
    else
    {
        modbusDevice->disconnectDevice();
    }

    ScanPortForDevices(1);
}

QList<IModbusDeviceDataManager::IModbusDeviceHandler*> ModbusDeviceDataManager::GetAvailableModbusDevices()
{
    QList<IModbusDeviceHandler*> deviceHandlersInterfaces;

    foreach (auto handler, deviceHandlers)
    {
        deviceHandlersInterfaces.append((IModbusDeviceHandler*)handler);
    }

    return deviceHandlersInterfaces;
}

void ModbusDeviceDataManager::ClosePort(QString portName)
{
}

void ModbusDeviceDataManager::OnDeviceConnectStateChanged()
{
}

void ModbusDeviceDataManager::SendReadRequest(const QModbusDataUnit &dataUnit)
{
    if (!modbusDevice)
        return;

    int deviceId = -1;

    if(!isScanPortForDevicesEnded)
    {
        deviceId = scanningDeviceId;
    }

    if(deviceId == -1)
    {
        auto deviceHandler = qobject_cast<ModbusDeviceHandler *>(sender());

        if(deviceHandler != NULL)
            deviceId = deviceHandler->GetDeviceId();
        else
            return;
    }

    if (auto *reply = modbusDevice->sendReadRequest(dataUnit, deviceId))
    {
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &ModbusDeviceDataManager::ReadReady);
        else
            delete reply; // broadcast replies return immediately
    }
    else
    {
        qDebug() << "Read error: " << modbusDevice->errorString();
    }
}

void ModbusDeviceDataManager::ReadReady()
{
    auto reply = qobject_cast<QModbusReply *>(sender());

    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError)
    {
        const QModbusDataUnit unit = reply->result();
        auto deviceId = reply->serverAddress();

        if(!deviceHandlers.contains(deviceId))
        {
            CreateNewDevice(deviceId);
        }

        if(isScanPortForDevicesEnded)
        {
            deviceHandlers[deviceId]->ReadDataUnit(unit);
        }
        else
        {
            qDebug() << "Found device with id" << deviceId;
            deviceHandlers[deviceId]->ReadServiceDataUnit(unit);
            isScanPortForDevicesEnded = true;
        }
    }
    else if (reply->error() == QModbusDevice::ProtocolError)
    {
        qDebug() << tr("Read response error: %1 (Mobus exception: 0x%2)").
                 arg(reply->errorString()).
                 arg(reply->rawResult().exceptionCode(), -1, 16);
    }
    else
    {
        qDebug() << tr("Read response error: %1 (code: 0x%2)").
                 arg(reply->errorString()).
                 arg(reply->error(), -1, 16);
    }

    reply->deleteLater();
}

void ModbusDeviceDataManager::CreateNewDevice(int deviceId)
{
    auto *newDevice = new ModbusDeviceHandler(deviceId, this);
    deviceHandlers.insert(deviceId, newDevice);
    connect(newDevice, &ModbusDeviceHandler::SendReadRequest, this, &ModbusDeviceDataManager::SendReadRequest);
    connect(newDevice, &ModbusDeviceHandler::SendWriteRequest, this, &ModbusDeviceDataManager::SendWriteRequest);
}

void ModbusDeviceDataManager::SendWriteRequest(const QModbusDataUnit &dataUnit)
{
    if (!modbusDevice)
        return;

    int deviceId = -1;

    if(!isScanPortForDevicesEnded)
    {
        deviceId = scanningDeviceId;
        isScanPortForDevicesEnded = true;
    }

    if(deviceId == -1)
    {
        auto deviceHandler = qobject_cast<ModbusDeviceHandler *>(sender());

        if(deviceHandler != NULL)
            deviceId = deviceHandler->GetDeviceId();
        else
            return;
    }

    if (auto *reply = modbusDevice->sendWriteRequest(dataUnit, deviceId))
    {
        if (!reply->isFinished())
        {
            connect(reply, &QModbusReply::finished, this, [this, reply]()
            {
                if (reply->error() == QModbusDevice::ProtocolError)
                {
                    qDebug() << tr("Write response error: %1 (Mobus exception: 0x%2)")
                             .arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16);
                }
                else if (reply->error() != QModbusDevice::NoError)
                {
                    qDebug() << tr("Write response error: %1 (code: 0x%2)").
                             arg(reply->errorString()).arg(reply->error(), -1, 16);
                }

                reply->deleteLater();
            });
        }
        else
        {
            // broadcast replies return immediately
            reply->deleteLater();
        }
    }
    else
    {
        qDebug() << tr("Write error: ") + modbusDevice->errorString();
    }
}
