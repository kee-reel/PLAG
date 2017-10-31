#include "devicedatahandler.h"

#include <QDebug>

DeviceDataHandler::DeviceDataHandler(ICOMPortDataSource::ISerialPortHandler *portHandler, QObject *parent) : QObject(parent)
{
    this->portHandler = portHandler;
    connect(portHandler->GetInstance(), SIGNAL(ReadData(QByteArray*)), this, SLOT(ReadData(QByteArray*)));
    connect(this, SIGNAL(WriteData(QByteArray &)), portHandler->GetInstance(), SLOT(WriteData(QByteArray &)));
    portHandler->OpenPort(QIODevice::ReadWrite);
}

void DeviceDataHandler::ReadData(QByteArray *buffer)
{
    qDebug() << "Read from device:" << (*buffer);
}
