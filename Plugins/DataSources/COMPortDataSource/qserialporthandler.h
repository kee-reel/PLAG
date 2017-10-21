#ifndef QSERIALPORTHANDLER_H
#define QSERIALPORTHANDLER_H

#include <QObject>
#include <QtGlobal>
#include <QSerialPort>
#include <QTimer>
#include <QSerialPortInfo>

#include "icomportdatasource.h"

class QSerialPortHandler : public QSerialPort, ICOMPortDataSource::IPortHandler
{
    Q_OBJECT
public:
    explicit QSerialPortHandler(QString portName, QObject *parent = nullptr);
    virtual ~QSerialPortHandler();

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
    bool OpenPort(QIODevice::OpenMode openMode) override;
    void ClosePort() override;
public slots:
    void WriteData(QByteArray &data) override;
signals:
    void ReadData(QByteArray *buffer);
};

#endif // QSERIALPORTHANDLER_H
