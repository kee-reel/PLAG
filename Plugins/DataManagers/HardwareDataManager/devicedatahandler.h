#ifndef DEVICEDATAHANDLER_H
#define DEVICEDATAHANDLER_H

#include <QObject>

#include "../../DataSources/COMPortDataSource/icomportdatasource.h"
#include "ihardwaredatamanager.h"

class DeviceDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit DeviceDataHandler(ICOMPortDataSource::ISerialPortHandler *portHandler, QObject *parent = nullptr);

signals:
    void WriteData(QByteArray &buffer);

public slots:

private:
    ICOMPortDataSource::ISerialPortHandler *portHandler;
    QByteArray lastMessage;
    IHardwareDataManager::IProtocolHandler *protocolHandler;

private slots:
    void ReadData(QByteArray *buffer);
};

#endif // DEVICEDATAHANDLER_H
