#include "qserialporthandler.h"

#include <QDebug>

QSerialPortHandler::QSerialPortHandler(QString portName, QObject *parent) : QSerialPort(parent)
{
    setPortName(portName);
    serialBufferSize = 50;
    connect(this, SIGNAL(readyRead()), this, SLOT(ReadDataPrivate()));
}

QSerialPortHandler::~QSerialPortHandler()
{
    ClosePort();
}

bool QSerialPortHandler::IsSupported() const
{
    return isSupported;
}

void QSerialPortHandler::SetIsSupported(bool value)
{
    isSupported = value;
}

bool QSerialPortHandler::OpenPort(QIODevice::OpenMode openMode)
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

void QSerialPortHandler::ClosePort()
{
    if (!isOpen())
        return;

    qDebug() << "Closing serial port" << QSerialPort::portName();
    close();
}

void QSerialPortHandler::WriteData(QByteArray &data)
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

    if(QSerialPort::write(data) == -1)
        qDebug() << "COM port" << QSerialPort::portName() << "write error:" << QSerialPort::errorString();
    else
        qDebug() << QString("Write to port %1:").arg(QSerialPort::portName()) << data;
}

void QSerialPortHandler::ReadDataPrivate()
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

QObject *QSerialPortHandler::GetInstance()
{
    return this;
}
