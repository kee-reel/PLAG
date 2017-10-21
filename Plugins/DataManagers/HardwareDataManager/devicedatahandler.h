#ifndef DEVICEDATAHANDLER_H
#define DEVICEDATAHANDLER_H

#include <QObject>

#include "../../DataSources/COMPortDataSource/icomportdatasource.h"

class DeviceDataHandler : public QObject
{
    Q_OBJECT
public:
    explicit DeviceDataHandler(ICOMPortDataSource::IPortHandler *portHandler, QObject *parent = nullptr);

signals:
    void WriteData(QByteArray &buffer);

public slots:

private:
    ICOMPortDataSource::IPortHandler *portHandler;
    QByteArray lastMessage;

private slots:
    void ReadData(QByteArray *buffer);
};

#endif // DEVICEDATAHANDLER_H
