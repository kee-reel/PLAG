#ifndef QSERIALPORTHANDLER_H
#define QSERIALPORTHANDLER_H

#include <QObject>
#include <QtGlobal>
#include <QSerialPort>
#include <QTimer>
#include <QSerialPortInfo>

#include "../../Interfaces/icomportdatamanager.h"

//!  \addtogroup COMPortDataManager_imp
//!  \{
class SerialPortHandler : public QSerialPort, ICOMPortDataManager::ISerialPortHandler
{
    Q_OBJECT
public:
    explicit SerialPortHandler(QString portName, QObject *parent = nullptr);
    virtual ~SerialPortHandler();

    bool IsSupported() const;
    void SetIsSupported(bool value);

private slots:
    void ReadDataPrivate();

private:
    QTimer *readTimer;
    int serialBufferSize;
    QByteArray serialBuffer;
    bool isSupported;

    // IPortHandler interface
public:
    QObject *GetInstance() override;
    QSerialPort *GetSerialPort() override;
    bool OpenPort(QIODevice::OpenMode openMode) override;
    void ClosePort() override;
public slots:
    void WriteData(QByteArray data) override;
signals:
    void ReadData(QByteArray *buffer);

};

#endif // QSERIALPORTHANDLER_H
