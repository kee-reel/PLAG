#include "modbusdevicehandler.h"

#include <QDebug>

ModbusDeviceHandler::ModbusDeviceHandler(int deviceId, QObject *parent) : QObject(parent)
{
    this->deviceId = deviceId;
}

QObject *ModbusDeviceHandler::GetInstance()
{
    return this;
}

int ModbusDeviceHandler::GetDeviceId()
{
    return deviceId;
}

bool ModbusDeviceHandler::ReadRequest(QModbusDataUnit::RegisterType dataType, int startAddress, int count)
{
    auto unit = QModbusDataUnit(dataType, startAddress, count);
    emit SendReadRequest(unit);
}

bool ModbusDeviceHandler::WriteRequest(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data)
{
    auto unit = QModbusDataUnit(dataType, startAddress, data);
    emit SendWriteRequest(unit);
}

void ModbusDeviceHandler::ReadDataUnit(const QModbusDataUnit &unit)
{
    //qDebug() << "New unit" << "Type:" << unit.registerType() << "Size:" << unit.valueCount();
    auto registerType = unit.registerType();
    //    QVector<quint16> *dataBuffer = GetDataBufferForType(registerType);
    //    if(dataBuffer->length() != unit.valueCount())
    //        dataBuffer->resize(unit.valueCount());
    //    for (uint i = 0; i < unit.valueCount(); ++i)
    //    {
    //        (*dataBuffer)[i] = unit.value(i);
    //        qDebug() << (unit.startAddress() + i) << (*dataBuffer)[i];
    //    }
    //    for (uint i = 0; i < unit.valueCount(); ++i)
    //    {
    //        qDebug() << (unit.startAddress() + i) << unit.value(i);
    //    }
    emit OnReadRequestArrived(registerType, unit.startAddress(), unit.values());
}

QVector<quint16> *ModbusDeviceHandler::GetDataBufferForType(QModbusDataUnit::RegisterType dataType)
{
    switch (dataType)
    {
        case QModbusDataUnit::DiscreteInputs:
            return &discreteInputsffer;
            break;

        case QModbusDataUnit::Coils:
            return &coilsBuffer;
            break;

        case QModbusDataUnit::InputRegisters:
            return &inputRegistersBuffer;
            break;

        case QModbusDataUnit::HoldingRegisters:
            return &holdingRegistersBuffer;
            break;

        default:
            return nullptr;
            break;
    }
}

void ModbusDeviceHandler::ReadServiceDataUnit(const QModbusDataUnit &dataUnit)
{
    if(dataUnit.valueCount() != 4)
        return;
}
