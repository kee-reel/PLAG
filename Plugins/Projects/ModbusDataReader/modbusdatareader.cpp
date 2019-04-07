#include "modbusdatareader.h"

#include <QDebug>

ModbusDataReader::ModbusDataReader() :
    PluginBase()
{
    myReferencedPlugin = nullptr;
    experimentState = false;
    AvailablePortsModel.setColumnCount(3);
    AvailablePortsModel.setHeaderData(0, Qt::Horizontal, "Port");
    AvailablePortsModel.setHeaderData(1, Qt::Horizontal, "Vendor");
    AvailablePortsModel.setHeaderData(2, Qt::Horizontal, "Device");
}

ModbusDataReader::~ModbusDataReader()
{
}

void ModbusDataReader::onAllReferencesSet()
{
    for(auto iter = m_referencesMap.begin(); iter != m_referencesMap.end(); ++iter)
    {
        auto&& interfaceName = iter.key();
        auto&& plugin = iter.value();
        if(!QString::compare(interfaceName, "IModbusDeviceDataManager", Qt::CaseInsensitive))
        {
            auto instance = plugin->getObject();
            myReferencedPlugin = qobject_cast<IModbusDeviceDataManager*>(instance);
            connect(instance, SIGNAL(ErrorOccurred(QString)), this, SIGNAL(ErrorOccurred(QString)));
            connect(instance, SIGNAL(ModbusListUpdated()), this, SLOT(UpdateDevicesList()));
        }
    }
    PluginBase::onAllReferencesSet();
}

void ModbusDataReader::UpdateDevicesList()
{
    auto devices = myReferencedPlugin->GetAvailableModbusDeviceHandlers();

    if(AvailableDevicesModel.rowCount() == 0 && devices.length() > 0)
        RegisterPacksModel.SetActiveDevice(devices.at(0));
    else if(devices.length() == 0)
        RegisterPacksModel.SetActiveDevice(nullptr);

    AvailableDevicesModel.UpdateDevicesList(devices);
}

void ModbusDataReader::ProcessDataInput(QModbusDataUnit::RegisterType dataType, const QVector<quint16> &data)
{
    qDebug() << "KEKS" << dataType << data;
}

void ModbusDataReader::StartReading()
{
    experimentStartTime = QDateTime::currentDateTime();
    RegisterPacksModel.CleanStoredData();
    RegisterPacksModel.SetStartTime(experimentStartTime);
    setProperty("ExperimentState", true);
}

void ModbusDataReader::StopReading()
{
    setProperty("ExperimentState", false);
}

QAbstractItemModel *ModbusDataReader::GetAvailablePorts()
{
    UpdateAvailablePorts();
    return &AvailablePortsModel;
}

void ModbusDataReader::UpdateAvailablePorts()
{
    auto ports = myReferencedPlugin->GetAvailablePorts();
    AvailablePortsModel.clear();

    foreach (auto port, ports)
    {
        QList<QStandardItem *> itemList =
        {
            new QStandardItem(port.portName),
            new QStandardItem(QString::number(port.vendorId)),
            new QStandardItem(QString::number(port.productId))
        };
        AvailablePortsModel.appendRow(itemList);
    }
}

bool ModbusDataReader::OpenPort(int modelIndex, IModbusDeviceDataManager::ConnectionSettings connectionSettings)
{
    myReferencedPlugin->OpenPort(AvailablePortsModel.item(modelIndex, 0)->text(), connectionSettings);
}

void ModbusDataReader::ScanForDevice(int deviceId)
{
    myReferencedPlugin->ScanForDevice(deviceId);
}

QAbstractItemModel *ModbusDataReader::GetAvailableModbusDeviceHandlers()
{
    return &AvailableDevicesModel;
}

QAbstractItemModel *ModbusDataReader::GetAvailableModbusDeviceNames()
{
    return AvailableDevicesModel.GetDeviceNamesModel();
}

void ModbusDataReader::ClosePort(int modelIndex)
{
}

QAbstractItemModel *ModbusDataReader::GetRegisterPacks()
{
    return &RegisterPacksModel;
}

void ModbusDataReader::SetDeviceForSetup(QString deviceName)
{
    auto *device = AvailableDevicesModel.GetDeviceByName(deviceName);
    RegisterPacksModel.SetActiveDevice(device);
}

QList<QLineSeries *> ModbusDataReader::GetRegistersLineSeries()
{
    return RegisterPacksModel.GetDataLineSeries();
}

void ModbusDataReader::AddRegisterPack(RegstersPack pack)
{
    RegisterPacksModel.AddRegisterPack(pack);
}

bool ModbusDataReader::GetReadingState()
{
    return experimentState;
}

QDateTime ModbusDataReader::GetReadingStartTime()
{
    return experimentStartTime;
}

bool ModbusDataReader::SaveReadingData(QString filename)
{
    QFile dataFile(filename);

    if(!dataFile.open(QIODevice::WriteOnly))
    {
        qCritical() << "Can't create file with filename" << filename << dataFile.errorString();
        return false;
    }

    QTextStream stream(&dataFile);
    stream << GetReadingStartTime().toString("hh:mm:ss.zzz") << "\r\n";
    auto lineSeries = GetRegistersLineSeries();

    foreach (auto line, lineSeries)
    {
        auto data = line->pointsVector();

        for(int i = 0; i < data.length(); ++i)
        {
            stream << data[i].x() << ";" << data[i].y() << "\r\n";
        }
    }
    return false;
}
