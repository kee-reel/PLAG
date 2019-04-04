#include "modbusdevicesmodel.h"

enum
{
    DeviceIdColumn = 0,
    DeviceNameColumn = 1,
    EnableColumn = 2,
    ColumnCount = 3
};

ModbusDevicesModel::ModbusDevicesModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int ModbusDevicesModel::rowCount(const QModelIndex &/*parent*/) const
{
    return devices.length();
}

int ModbusDevicesModel::columnCount(const QModelIndex &/*parent*/) const
{
    return ColumnCount;
}

QVariant ModbusDevicesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= devices.length() || index.column() >= ColumnCount)
        return QVariant();

    auto device = devices.at(index.row());
    if(role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case DeviceNameColumn:
            return QVariant(devicesExtraData.value(device).name);
        case DeviceIdColumn:
            return QVariant(device->GetDeviceId());
        default:
            break;
        }
    }

    if (role == Qt::CheckStateRole && index.column() == EnableColumn)
        return devicesExtraData.value(device).enabled ? Qt::Checked : Qt::Unchecked;

    return QVariant();

}

QVariant ModbusDevicesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case DeviceIdColumn:
            return QStringLiteral("Device Id");
        case DeviceNameColumn:
            return QStringLiteral("Name");
        case EnableColumn:
            return QStringLiteral("Enable");
        default:
            break;
        }
    }
    return QVariant();
}

bool ModbusDevicesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= devices.length() || index.column() >= ColumnCount)
        return false;

    auto device = devices.at(index.row());

    if (index.column() == EnableColumn)
    {
        auto s = static_cast<Qt::CheckState>(value.toUInt());
        if(s == Qt::Checked)
        {
            devicesExtraData[device].enabled = true;
            QString uniqueName = QString("%1 (%2)")
                    .arg(devicesExtraData[device].name)
                    .arg(device->GetDeviceId());
            InsertModelDeviceName(index.row(), uniqueName);
        }
        else
        {
            devicesExtraData[device].enabled = false;
            devicesNamesModel.removeRow(index.row());
        }


        emit dataChanged(index, index);
        return true;
    }

    if(index.column() == DeviceNameColumn)
    {
        auto str = value.toString();
        if(str == "")
            return false;
        devicesExtraData[device].name = str;
        devicesNamesModel.setData(devicesNamesModel.index(index.row()), str);
        emit dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags ModbusDevicesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= devices.length() || index.column() >= ColumnCount)
        return QAbstractTableModel::flags(index);

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

//    if (pack.type == QModbusDataUnit::InputRegisters || pack.type == QModbusDataUnit::DiscreteInputs)
//        flags &= ~Qt::ItemIsEnabled;

    if (index.column() == EnableColumn)
        flags |= Qt::ItemIsUserCheckable;

    if(index.column() == DeviceNameColumn || index.column() == EnableColumn)
        flags |= Qt::ItemIsEditable;

    return flags;
}

void ModbusDevicesModel::InsertModelDeviceName(int row, QString uniqueName)
{
    devicesNamesModel.insertRows(row, 1);
    devicesNamesModel.setData(devicesNamesModel.index(row), uniqueName);
}

void ModbusDevicesModel::UpdateDevicesList(QList<IModbusDeviceDataManager::IModbusDeviceHandler *> devices)
{
    if(this->devices.length() < devices.length())
    {
        beginRemoveRows(QModelIndex(), 0, this->devices.length());
        this->devices.clear();
        endRemoveRows();
    }

    foreach (auto device, devices)
    {
        if(!this->devices.contains(device))
        {
            beginInsertRows(QModelIndex(), this->devices.length(), this->devices.length());
            this->devices.append(device);
            devicesExtraData[device].name = QString("Dev%1").arg(device->GetDeviceId());
            devicesExtraData[device].enabled = true;

            QString uniqueName = QString("%1 (%2)")
                    .arg(devicesExtraData[device].name)
                    .arg(device->GetDeviceId());
            InsertModelDeviceName(devicesNamesModel.rowCount(), uniqueName);

            endInsertRows();
        }
    }
}

QStringListModel *ModbusDevicesModel::GetDeviceNamesModel()
{
    return &devicesNamesModel;
}

IModbusDeviceDataManager::IModbusDeviceHandler *ModbusDevicesModel::GetDeviceByName(QString deviceName)
{
    auto iter = devicesExtraData.begin();
    while(iter != devicesExtraData.end())
    {
        DeviceExtraData value = iter.value();
        if(value.name == deviceName)
            return iter.key();
        ++iter;
    }
    return nullptr;
}

bool ModbusDevicesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(rowCount() > row)
    {
        beginRemoveRows(QModelIndex(), row, row+count);
        for(int i = 0; i < count; ++i)
            devices.removeAt(row);
        endRemoveRows();
    }
}
