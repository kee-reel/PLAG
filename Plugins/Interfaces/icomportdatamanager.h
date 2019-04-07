#ifndef ICOMPortDataManager_H
#define ICOMPortDataManager_H

#include <QtGlobal>
#include <QSerialPort>

//!  \defgroup COMPortDataManager COMPortDataManager
//!      \ingroup Plugins
//!  \defgroup COMPortDataManager_int Interface
//!      \ingroup COMPortDataManager
//!  \defgroup COMPortDataManager_imp Implementation
//!      \ingroup COMPortDataManager
//!  \defgroup COMPortDataManager_dep Dependent plugins
//!      \ingroup COMPortDataManager

//!  \addtogroup COMPortDataManager_int
//!  \{
class ICOMPortDataManager
{
public:
    //!
    //! \brief The DeviceInfo struct
    //! Identifies device
    struct DeviceInfo
    {
        quint16 vendorId;
        quint16 productId;
    };

    class ISerialPortHandler
    {
    public:
        DeviceInfo connectedDeviceInfo;

        virtual QObject *GetInstance() = 0;
        virtual QSerialPort *GetSerialPort() = 0;
        virtual bool OpenPort(QIODevice::OpenMode openMode) = 0;
        virtual void ClosePort() = 0;
    public slots:
        virtual void WriteData(QByteArray data) = 0;
    signals:
        //!
        //! \brief ReadData
        //! \param buffer
        //! After emitting this signal buffer wipes out.
        //!
        void ReadData(QByteArray *buffer);
    };

    virtual void AddSupportedDevice(QString deviceName, DeviceInfo &deviceInfo) = 0;
    virtual QMap<QString, DeviceInfo> GetSupportedDevices() = 0;
    virtual QMap<QString, ISerialPortHandler*> GetPortHandlers() = 0;
};
//!  \}
Q_DECLARE_INTERFACE(ICOMPortDataManager, "ICOMPortDataManager")
#endif // ICOMPortDataManager_H
