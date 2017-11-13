#include "modbusdevicehandler.h"

#include <QDebug>

ModbusDeviceHandler::ModbusDeviceHandler(int deviceId, QObject *parent) : QObject(parent)
{
    this->deviceId = deviceId;
    startAddress = 0;
}

QObject *ModbusDeviceHandler::GetInstance()
{
    return this;
}

int ModbusDeviceHandler::GetDeviceId()
{
    return deviceId;
}

int ModbusDeviceHandler::GetDeviceTime()
{
    return deviceTime;
}

int ModbusDeviceHandler::GetBufferSize(QModbusDataUnit::RegisterType dataType)
{
    auto *buffer = GetDataBufferForType(dataType);

    if(!buffer)
        return -1;

    return buffer->length();
}

bool ModbusDeviceHandler::ReadRequest(QModbusDataUnit::RegisterType dataType, int startAddress)
{
    auto buffer = GetDataBufferForType(dataType);
    auto unit = QModbusDataUnit(dataType, startAddress, buffer->size());
    emit SendReadRequest(unit);
}

bool ModbusDeviceHandler::WriteRequest(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data)
{
    auto unit = QModbusDataUnit(dataType, startAddress, data);
    emit SendWriteRequest(unit);
}

void ModbusDeviceHandler::ReadDataUnit(const QModbusDataUnit &unit)
{
    qDebug() << "New unit" << "Type:" << unit.registerType() << "Size:" << unit.valueCount();
    auto registerType = unit.registerType();
    QVector<quint16> *dataBuffer = GetDataBufferForType(registerType);

    if(dataBuffer->length() != unit.valueCount())
        return;

    for (uint i = 0; i < unit.valueCount(); ++i)
    {
        (*dataBuffer)[i] = unit.value(i);
        qDebug() << (unit.startAddress() + i) << (*dataBuffer)[i];
    }

    emit OnReadRequestArrived(registerType, *dataBuffer);
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
            return NULL;
            break;
    }
}

void ModbusDeviceHandler::ReadServiceDataUnit(const QModbusDataUnit &dataUnit)
{
    if(dataUnit.valueCount() != 4)
        return;
}

void ModbusDeviceHandler::SetBufferSize(QModbusDataUnit::RegisterType dataType, int size)
{
    auto *buffer = GetDataBufferForType(dataType);

    if(!buffer)
        return;

    buffer->resize(size);
}
