#include "serialporthandler.h"

#include <QDebug>

SerialPortHandler::SerialPortHandler(QString portName, QObject *parent) : QSerialPort(parent)
{
    setPortName(portName);
    auto info = QSerialPortInfo(portName);
    connectedDeviceInfo.productId = info.productIdentifier();
    connectedDeviceInfo.vendorId = info.vendorIdentifier();
    serialBufferSize = 50;
    connect(this, SIGNAL(readyRead()), this, SLOT(ReadDataPrivate()));
}

SerialPortHandler::~SerialPortHandler()
{
    ClosePort();
}

bool SerialPortHandler::IsSupported() const
{
    return isSupported;
}

void SerialPortHandler::SetIsSupported(bool value)
{
    isSupported = value;
}

bool SerialPortHandler::OpenPort(QIODevice::OpenMode openMode)
{
    if(!isSupported)
    {
        qDebug() << "COM port" << QSerialPort::portName() << "open error: Device protocol not supported by system.";
        return false;
    }

    if (QSerialPort::isOpen())
        ClosePort();

    if (!QSerialPort::open(openMode))
    {
        qDebug() << "COM port" << QSerialPort::portName() << "open error:" << QSerialPort::errorString();
        return false;
    }

    QSerialPort::setBaudRate(QSerialPort::Baud9600);
    QSerialPort::setDataBits(QSerialPort::Data8);
    QSerialPort::setParity(QSerialPort::NoParity);
    QSerialPort::setStopBits(QSerialPort::OneStop);
    QSerialPort::setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "COM port" << QSerialPort::portName() << "now connected.";
    return true;
}

void SerialPortHandler::ClosePort()
{
    if (!isOpen())
        return;

    qDebug() << "Closing serial port" << QSerialPort::portName();
    close();
}

void SerialPortHandler::WriteData(QByteArray data)
{
    if (!QSerialPort::isOpen())
    {
        qDebug() << "COM port" << QSerialPort::portName() << "write error: Port isn't opened.";
        return;
    }

    if (!QSerialPort::isWritable())
    {
        qDebug() << "COM port" << QSerialPort::portName() << "write error: Port isn't writable.";
        return;
    }

    if(QSerialPort::write(data) != -1)
        qDebug() << QString("Write to port %1:").arg(QSerialPort::portName()) << data;
    else
        qDebug() << "COM port" << QSerialPort::portName() << "write error:" << QSerialPort::errorString();
}

void SerialPortHandler::ReadDataPrivate()
{
    serialBuffer = QSerialPort::readAll();

    if (serialBuffer.length() != 0)
    {
        emit ReadData(&serialBuffer);
        serialBuffer.clear();
    }
    else
    {
        qDebug() << "Read zero bytes";
    }
}

QObject *SerialPortHandler::GetInstance()
{
    return this;
}

QSerialPort *SerialPortHandler::GetSerialPort()
{
    return this;
}
