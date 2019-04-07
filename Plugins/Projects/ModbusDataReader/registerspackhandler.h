#ifndef REGISTERSPACKHANDLER_H
#define REGISTERSPACKHANDLER_H

#include <QObject>
#include "../../Interfaces/imodbusdatareader.h"

class RegistersPackHandler : public QObject, public IModbusDataReader::RegstersPack
{
    Q_OBJECT
public:
    class RegisterHandler
    {
    public:
        RegistersPackHandler *parentItem;
        QLineSeries dataSeries;
        QString name;
        int index;

        RegisterHandler(RegistersPackHandler *parent, int index);
        int GetAddress();
        void SetData(const qreal &x, const quint16 &y);
        quint16 GetData();
    };

    QVector<quint16> data;
    QVector<RegisterHandler*> registerHandlers;

    explicit RegistersPackHandler(IModbusDataReader::RegstersPack &pack,
                                  IModbusDeviceDataManager::IModbusDeviceHandler *device, QObject *parent = 0);
    ~RegistersPackHandler();
    void FillRegistersHash(int startHash, QHash<int, QLineSeries *> &hash);
    void SetDataPack(qreal &xValue, const QVector<quint16> &data);

signals:

public slots:

private:
    QTimer updateTimer;
    int hashValue;
};

#endif // REGISTERSPACKHANDLER_H
