#ifndef MODBUSDEVICEHANDLER_H
#define MODBUSDEVICEHANDLER_H

#include <QModbusDataUnit>
#include <QObject>

#include "../../Interfaces/imodbusdevicedatamanager.h"

class ModbusDeviceHandler : public QObject, IModbusDeviceDataManager::IModbusDeviceHandler
{
    Q_OBJECT
public:
    explicit ModbusDeviceHandler(int deviceId, QObject *parent = nullptr);

    // IModbusDeviceHandler interface
public:
    QObject *GetInstance() override;
    int GetDeviceId() override;
public slots:
    bool ReadRequest(QModbusDataUnit::RegisterType dataType, int startAddress, int count) override;
    bool WriteRequest(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data) override;
signals:
    void OnReadRequestArrived(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data);

private:
    int deviceId;
    QVector<quint16> discreteInputsffer;
    QVector<quint16> coilsBuffer;
    QVector<quint16> inputRegistersBuffer;
    QVector<quint16> holdingRegistersBuffer;

    QVector<quint16> *GetDataBufferForType(QModbusDataUnit::RegisterType dataType);

public:
    void ReadServiceDataUnit(const QModbusDataUnit &dataUnit);
public slots:
    void ReadDataUnit(const QModbusDataUnit &unit);
signals:
    void SendReadRequest(const QModbusDataUnit &unit);
    void SendWriteRequest(const QModbusDataUnit &unit);

};

#endif // MODBUSDEVICEHANDLER_H
