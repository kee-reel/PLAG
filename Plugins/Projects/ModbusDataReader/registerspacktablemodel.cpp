#include "registerspacktablemodel.h"

enum
{
    TypeColumn = 0,
    StartColumn = 1,
    CountColumn = 2,
    UpdateIntervalColumn = 3,
    ColumnCount = 4
};

RegistersPackTableModel::RegistersPackTableModel(QObject *parent) : QAbstractItemModel(parent)
{
    activePacks = nullptr;
    experimentStartTime = QDateTime::currentMSecsSinceEpoch();
}

int RegistersPackTableModel::rowCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return activePacks != nullptr ? activePacks->length() : 0;
    }

    auto pack = static_cast<RegistersPackHandler*>(parent.internalPointer());

    if(pack != nullptr)
    {
        return pack->count;
    }

    auto reg = static_cast<RegistersPackHandler::RegisterHandler*>(parent.internalPointer());

    if(reg != nullptr)
    {
        return 0;
    }
}

int RegistersPackTableModel::columnCount(const QModelIndex &parent) const
{
    if(!parent.isValid())
    {
        return ColumnCount;
    }
    else
    {
        return 3;
    }
}

QVariant RegistersPackTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || activePacks == nullptr)
        return QVariant();

    if(!index.parent().isValid())
    {
        auto pack = static_cast<RegistersPackHandler*>(index.internalPointer());

        if(pack != nullptr)
        {
            auto pack = activePacks->at(index.row());

            if(role == Qt::DisplayRole)
            {
                switch (index.column())
                {
                    case TypeColumn:
                        return QVariant( GetRegisterString(pack->type) );

                    case StartColumn:
                        return QVariant(pack->start);

                    case CountColumn:
                        return QVariant(pack->count);

                    case UpdateIntervalColumn:
                        return QVariant(pack->updateInterval);

                    default:
                        break;
                }
            }
        }
    }
    else
    {
        auto reg = static_cast<RegistersPackHandler::RegisterHandler*>(index.internalPointer());

        if(reg != nullptr)
        {
            if(role == Qt::DisplayRole)
            {
                switch (index.column())
                {
                    case TypeColumn:
                        return QVariant(reg->GetAddress());

                    case StartColumn:
                        return QVariant(reg->name);

                    case CountColumn:
                        return QVariant(reg->GetData());

                    default:
                        break;
                }
            }
        }
    }

    //    if (index.column() == NumColumn && role == Qt::DisplayRole)
    //        return QString::number(index.row());
    //    if (index.column() == CoilsColumn && role == Qt::CheckStateRole) // coils
    //        return m_coils.at(index.row()) ? Qt::Checked : Qt::Unchecked;
    //    else if (index.column() == HoldingColumn && role == Qt::DisplayRole) //holding registers
    //        return QString("0x%1").arg(QString::number(m_holdingRegisters.at(index.row()), 16));
    return QVariant();
}

QVariant RegistersPackTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case TypeColumn:
                return QStringLiteral("Type");

            case StartColumn:
                return QStringLiteral("Start");

            case CountColumn:
                return QStringLiteral("Count");

            case UpdateIntervalColumn:
                return QStringLiteral("Interval");

            default:
                break;
        }
    }

    return QVariant();
}

bool RegistersPackTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || activePacks == nullptr || index.row() >= activePacks->length() || index.column() >= ColumnCount)
        return false;

    //    if (index.column() == CoilsColumn && role == Qt::CheckStateRole)
    //    { // coils
    //        auto s = static_cast<Qt::CheckState>(value.toUInt());
    //        s == Qt::Checked ? m_coils.setBit(index.row()) : m_coils.clearBit(index.row());
    //        emit dataChanged(index, index);
    //        return true;
    //    }
    //    if (index.column() == HoldingColumn && Qt::EditRole) { // holding registers
    //        bool result = false;
    //        quint16 newValue = value.toString().toUShort(&result, 16);
    //        if (result)
    //            m_holdingRegisters[index.row()] = newValue;
    //        emit dataChanged(index, index);
    //        return result;
    //    }
    return false;
}

Qt::ItemFlags RegistersPackTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || activePacks == nullptr || index.row() >= activePacks->length() || index.column() >= ColumnCount)
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    auto pack = activePacks->at(index.row());
    //    if (pack.type == QModbusDataUnit::InputRegisters || pack.type == QModbusDataUnit::DiscreteInputs)
    //        flags &= ~Qt::ItemIsEnabled;
    //    if (index.column() == CoilsColumn) //coils
    //        return flags | Qt::ItemIsUserCheckable;
    //    if (index.column() == HoldingColumn) //holding registers
    //        return flags | Qt::ItemIsEditable;
    return flags;
}

IModbusDataReader::RegstersPack *RegistersPackTableModel::FindExistedPack(IModbusDataReader::RegstersPack pack)
{
    foreach(auto registersPack, (*activePacks))
    {
        if(registersPack->type == pack.type &&
                registersPack->start == pack.start &&
                registersPack->count == pack.count)
        {
            return registersPack;
        }
    }

    return nullptr;
}

void RegistersPackTableModel::AddRegisterPack(IModbusDataReader::RegstersPack pack)
{
    if(activePacks == nullptr)
        return;

    IModbusDataReader::RegstersPack *foundPack = FindExistedPack(pack);

    if(foundPack == nullptr)
    {
        emit beginInsertRows(QModelIndex(), activePacks->length(), activePacks->length());
        RegistersPackHandler *valuesPack = new RegistersPackHandler(pack, activeDevice, this);
        activePacks->append(valuesPack);
        int hashValue = activeDevice->GetDeviceId() * (int)pack.type * pack.start * pack.count;
        registerPacksHash.insert(hashValue, valuesPack);
        valuesPack->FillRegistersHash(hashValue, registersLineSeriesHash);
        emit endInsertRows();
    }
}

void RegistersPackTableModel::ReadRegistersPack(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data)
{
    //qDebug() << "Pack read:" << dataType << startAddress << data;
    int hashValue = 1 * (int)dataType * startAddress * data.length();
    auto iter = registerPacksHash.find(hashValue);

    if(iter != registerPacksHash.end())
    {
        auto pack = iter.value();
        qreal xValue = (qreal)(QDateTime::currentMSecsSinceEpoch() - experimentStartTime);
        xValue /= 1000.;
        pack->SetDataPack(xValue, data);
        auto parentIndex = createIndex(0, 0, pack);
        dataChanged(index(0, 3, parentIndex), index(pack->count-1, 3, parentIndex));
    }

    //    auto senderDevice = qobject_cast<IModbusDeviceDataManager::IModbusDeviceHandler *>(sender());
    //    if (!senderDevice)
    //        return;
    //    if(!devicesPacks.contains(senderDevice))
    //    {
    //        int hashValue = senderDevice->GetDeviceId() * (int)dataType * startAddress * data.length();
    //        auto packHandler = registerPacksHash.value(hashValue);
    //        if(packHandler != nullptr)
    //            packHandler->data = data;
    //    }
}

void RegistersPackTableModel::SetActiveDevice(IModbusDeviceDataManager::IModbusDeviceHandler *device)
{
    beginResetModel();
    activeDevice = device;

    if(activeDevice == nullptr)
    {
        activePacks = nullptr;
    }
    else
    {
        if(!devicesPacks.contains(activeDevice))
        {
            devicesPacks.insert(activeDevice, QList<RegistersPackHandler*>());
            connect(activeDevice->GetInstance(), SIGNAL(OnReadRequestArrived(QModbusDataUnit::RegisterType, int, QVector<quint16>)),
                    this, SLOT(ReadRegistersPack(QModbusDataUnit::RegisterType, int, QVector<quint16>))
                   );
        }

        activePacks = &devicesPacks[activeDevice];
    }

    endResetModel();
}

QList<QLineSeries *> RegistersPackTableModel::GetDataLineSeries()
{
    return registersLineSeriesHash.values();
}

void RegistersPackTableModel::CleanStoredData()
{
    auto hash = GetDataLineSeries();

    foreach (auto item, hash)
    {
        item->clear();
    }
}

void RegistersPackTableModel::SetStartTime(QDateTime experimentStartTime)
{
    this->experimentStartTime = experimentStartTime.toMSecsSinceEpoch();
}

QString RegistersPackTableModel::GetRegisterString(QModbusDataUnit::RegisterType type) const
{
    switch (type)
    {
        case QModbusDataUnit::Invalid:
            return "Invalid";
            break;

        case QModbusDataUnit::DiscreteInputs:
            return "DiscreteInputs";
            break;

        case QModbusDataUnit::Coils:
            return "Coils";
            break;

        case QModbusDataUnit::InputRegisters:
            return "InputRegisters";
            break;

        case QModbusDataUnit::HoldingRegisters:
            return "HoldingRegisters";
            break;

        default:
            return "";
    }
}

QModbusDataUnit::RegisterType RegistersPackTableModel::GetRegisterType(QString str) const
{
    if(str == "DiscreteInputs")
        return QModbusDataUnit::DiscreteInputs;
    else if(str == "Coils")
        return QModbusDataUnit::Coils;
    else if(str == "InputRegisters")
        return QModbusDataUnit::InputRegisters;
    else if(str == "HoldingRegisters")
        return QModbusDataUnit::HoldingRegisters;
    else
        return QModbusDataUnit::Invalid;
}


bool RegistersPackTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(activePacks->length() > row)
    {
        beginRemoveRows(QModelIndex(), row, row+count-1);

        for(int i = 0; i < count; ++i)
        {
            delete (*activePacks)[row];
            activePacks->removeAt(row);
        }

        endRemoveRows();
    }
}

QModelIndex RegistersPackTableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (!parent.isValid())
    {
        if(activePacks == nullptr || activePacks->length() <= row)
            return QModelIndex();

        RegistersPackHandler* item = activePacks->at(row);
        return createIndex(row, column, item);
    }

    auto parentItem = static_cast<RegistersPackHandler*>(parent.internalPointer());

    if(parentItem != nullptr)
    {
        return createIndex(row, column, parentItem->registerHandlers[row]);
    }

    return QModelIndex();
}

QModelIndex RegistersPackTableModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    auto reg = static_cast<RegistersPackHandler::RegisterHandler*>(index.internalPointer());

    if(reg != nullptr && activePacks != nullptr)
    {
        RegistersPackHandler* item = reg->parentItem;
        int row = activePacks->indexOf(item);

        if(row != -1)
            return createIndex(row, 0, item);
    }

    auto pack = static_cast<RegistersPackHandler*>(index.internalPointer());

    if(pack != nullptr && activePacks != nullptr)
    {
        return QModelIndex();
    }

    return QModelIndex();
}
