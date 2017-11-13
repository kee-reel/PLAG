#ifndef MODBUSDEVICEHANDLER_H
#define MODBUSDEVICEHANDLER_H

#include <QModbusDataUnit>
#include <QObject>

#include "imodbusdevicedatamanager.h"

class ModbusDeviceHandler : public QObject, IModbusDeviceDataManager::IModbusDeviceHandler
{
    Q_OBJECT
public:
    explicit ModbusDeviceHandler(int deviceId, QObject *parent = nullptr);

    // IModbusDeviceHandler interface
public:
    QObject *GetInstance() override;
    int GetDeviceId() override;
    int GetDeviceTime() override;
    int GetBufferSize(QModbusDataUnit::RegisterType dataType) override;
public slots:
    bool ReadRequest(QModbusDataUnit::RegisterType dataType, int startAddress) override;
    bool WriteRequest(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data) override;
signals:
    void OnReadRequestArrived(QModbusDataUnit::RegisterType dataType, const QVector<quint16> &data);

private:
    int deviceId;
    int deviceTime;
    int startAddress;
    QVector<quint16> discreteInputsffer;
    QVector<quint16> coilsBuffer;
    QVector<quint16> inputRegistersBuffer;
    QVector<quint16> holdingRegistersBuffer;

    QVector<quint16> *GetDataBufferForType(QModbusDataUnit::RegisterType dataType);

    void SetBufferSize(QModbusDataUnit::RegisterType dataType, int size);
public:
    void ReadServiceDataUnit(const QModbusDataUnit &dataUnit);
public slots:
    void ReadDataUnit(const QModbusDataUnit &unit);
signals:
    void SendReadRequest(const QModbusDataUnit &unit);
    void SendWriteRequest(const QModbusDataUnit &unit);

};

#endif // MODBUSDEVICEHANDLER_H
