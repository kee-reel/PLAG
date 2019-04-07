#ifndef IModbusDataReader_H
#define IModbusDataReader_H

#include "imodbusdevicedatamanager.h"
#include <QtCore>
#include <QtCharts>
#include <QSerialPort>
#include <QModbusDataUnit>

//!  \defgroup ModbusDataReader ModbusDataReader
//!      \ingroup Plugins
//!  \defgroup ModbusDataReader_int Interface
//!      \ingroup ModbusDataReader
//!  \defgroup ModbusDataReader_imp Implementation
//!      \ingroup ModbusDataReader
//!  \defgroup ModbusDataReader_dep Dependent plugins
//!      \ingroup ModbusDataReader

//!  \addtogroup ModbusDataReader_int
//!  \{
class IModbusDataReader
{
public:

    virtual bool GetReadingState() = 0;
    virtual void StartReading() = 0;
    virtual void StopReading() = 0;
    virtual QDateTime GetReadingStartTime() = 0;
    virtual bool SaveReadingData(QString filename) = 0;

    struct PortInfo
    {
        QString portName;
        int productId;
        int vendorId;
    };

    virtual QAbstractItemModel *GetAvailablePorts() = 0;
    virtual void UpdateAvailablePorts() = 0;
    virtual bool OpenPort(int modelIndex, IModbusDeviceDataManager::ConnectionSettings connectionSettings) = 0;
    virtual void ScanForDevice(int deviceId) = 0;
    virtual QAbstractItemModel *GetAvailableModbusDeviceHandlers() = 0;
    virtual QAbstractItemModel *GetAvailableModbusDeviceNames() = 0;
    virtual void ClosePort(int modelIndex) = 0;

    struct RegstersPack
    {
        QModbusDataUnit::RegisterType type;
        int start;
        int count;
        int updateInterval;
    };

    virtual QAbstractItemModel *GetRegisterPacks() = 0;
    virtual void SetDeviceForSetup(QString deviceName) = 0;
    virtual void AddRegisterPack(RegstersPack pack) = 0;

    virtual QList<QLineSeries*> GetRegistersLineSeries() = 0;

signals:
    void ErrorOccurred(QString error);
    void ExperimentStateChanged(bool state);
};
//!  \}
Q_DECLARE_INTERFACE(IModbusDataReader, "IModbusDataReader")
#endif // IModbusDataReader_H
