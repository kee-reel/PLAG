#include "registervaluesmodel.h"

enum
{
    TypeColumn = 0,
    StartColumn = 1,
    CountColumn = 2,
    UpdateIntervalColumn = 3,
    ColumnCount = 4
};

RegisterValuesModel::RegisterValuesModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int RegisterValuesModel::rowCount(const QModelIndex &/*parent*/) const
{
    return packs.length();
}

int RegisterValuesModel::columnCount(const QModelIndex &/*parent*/) const
{
    return ColumnCount;
}

QVariant RegisterValuesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= packs.length() || index.column() >= ColumnCount)
        return QVariant();

    auto pack = packs.at(index.row());
    if(role == Qt::DisplayRole)
    {
        switch (index.column())
        {
        case TypeColumn:
            return QVariant( GetRegisterString(pack.type) );
        case StartColumn:
            return QVariant(pack.start);
        case CountColumn:
            return QVariant(pack.count);
        case UpdateIntervalColumn:
            return QVariant(pack.updateInterval);
        default:
            break;
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

QVariant RegisterValuesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
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

bool RegisterValuesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() >= packs.length() || index.column() >= ColumnCount)
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

Qt::ItemFlags RegisterValuesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.row() >= packs.length() || index.column() >= ColumnCount)
        return QAbstractTableModel::flags(index);

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    auto pack = packs.at(index.row());

//    if (pack.type == QModbusDataUnit::InputRegisters || pack.type == QModbusDataUnit::DiscreteInputs)
//        flags &= ~Qt::ItemIsEnabled;

//    if (index.column() == CoilsColumn) //coils
//        return flags | Qt::ItemIsUserCheckable;
//    if (index.column() == HoldingColumn) //holding registers
//        return flags | Qt::ItemIsEditable;

    return flags;
}

IExperimentControlModel::RegstersPack *RegisterValuesModel::FindExistedPack(IExperimentControlModel::RegstersPack pack)
{
    foreach(auto registersPack, packs)
    {
        if(registersPack.type == pack.type &&
                registersPack.start == pack.start &&
                registersPack.count == pack.count)
        {
            return &registersPack;
        }
    }
    return NULL;
}

void RegisterValuesModel::AddRegisterPack(IExperimentControlModel::RegstersPack pack)
{
    IExperimentControlModel::RegstersPack *foundPack = FindExistedPack(pack);

    if(foundPack == NULL)
    {
        emit beginInsertRows(QModelIndex(), packs.length(), packs.length());
        packs.append(pack);
        emit endInsertRows();
    }
}

void RegisterValuesModel::RemoveRegisterPack(int row)
{
    if(packs.length() > row)
    {
        beginRemoveRows(QModelIndex(), row, row);
        packs.removeAt(row);
        endRemoveRows();
    }
}

QString RegisterValuesModel::GetRegisterString(QModbusDataUnit::RegisterType type) const
{
    switch (type) {
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

QModbusDataUnit::RegisterType RegisterValuesModel::GetRegisterType(QString str) const
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
