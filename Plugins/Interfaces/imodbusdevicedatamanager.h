#ifndef IMODBUSDEVICEDATAMANAGER_H
#define IMODBUSDEVICEDATAMANAGER_H

#include <QtCore>
#include <QSerialPort>
#include <QModbusDataUnit>

//!  \defgroup ModbusDeviceDataManager ModbusDeviceDataManager
//!      \ingroup Plugins
//!  \defgroup ModbusDeviceDataManager_int Interface
//!      \ingroup ModbusDeviceDataManager
//!  \defgroup ModbusDeviceDataManager_imp Implementation
//!      \ingroup ModbusDeviceDataManager
//!  \defgroup ModbusDeviceDataManager_dep Dependent plugins
//!      \ingroup ModbusDeviceDataManager

//!  \addtogroup ModbusDeviceDataManager_int
//!  \{
class IModbusDeviceDataManager
{
public:
    struct PortInfo
    {
        QString portName;
        int productId;
        int vendorId;
    };

    struct ConnectionSettings
    {
        QSerialPort::Parity parity;
        QSerialPort::BaudRate baud;
        QSerialPort::DataBits dataBits;
        QSerialPort::StopBits stopBits;
        int responseTimeout;
        int numberOfRetries;
    };

    class IModbusDeviceHandler
    {
    public:
        virtual QObject *GetInstance() = 0;
        virtual int GetDeviceId() = 0;
    public slots:
        virtual bool ReadRequest(QModbusDataUnit::RegisterType dataType, int startAddress, int count) = 0;
        virtual bool WriteRequest(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data) = 0;
    signals:
        void OnReadRequestArrived(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data);
    };

    virtual QList<PortInfo> GetAvailablePorts() = 0;
    virtual bool OpenPort(QString portName, ConnectionSettings connectionSettings) = 0;
    virtual void ScanForDevice(int deviceId) = 0;
    virtual QList<IModbusDeviceHandler*> GetAvailableModbusDeviceHandlers() = 0;
    virtual void ClosePort(QString portName) = 0;

signals:
    void ErrorOccurred(QString error);
    void ModbusListUpdated();
};
//!  \}
Q_DECLARE_INTERFACE(IModbusDeviceDataManager, "IModbusDeviceDataManager")
#endif // IMODBUSDEVICEDATAMANAGER_H
