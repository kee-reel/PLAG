#include "registerspackhandler.h"

RegistersPackHandler::RegistersPackHandler(RegstersPack &pack, IModbusDeviceDataManager::IModbusDeviceHandler *device,
        QObject *parent)
    : QObject(parent)
{
    type = pack.type;
    start = pack.start;
    count = pack.count;
    updateInterval = pack.updateInterval;
    data = QVector<quint16>(count);
    registerHandlers = QVector<RegisterHandler*>(count);

    for(int i = 0; i < count; ++i)
        registerHandlers[i] = new RegisterHandler(this, i);

    connect(&updateTimer, &QTimer::timeout, this, [=]()
    {
        device->ReadRequest(type, start, count);
    });
    updateTimer.start(updateInterval);
}

RegistersPackHandler::~RegistersPackHandler()
{
    updateTimer.stop();

    for (int i = 0; i < registerHandlers.length(); ++i)
    {
        delete registerHandlers[i];
    }
}

void RegistersPackHandler::FillRegistersHash(int startHash, QHash<int, QLineSeries*> &hash)
{
    for (int i = 0; i < count; ++i)
    {
        hash.insert(startHash+i, &registerHandlers[i]->dataSeries);
    }
}

void RegistersPackHandler::SetDataPack(qreal &xValue, const QVector<quint16> &data)
{
    for (int i = 0; i < count; ++i)
    {
        registerHandlers[i]->SetData(xValue, data.at(i));
    }
}

RegistersPackHandler::RegisterHandler::RegisterHandler(RegistersPackHandler *parent, int index)
{
    this->parentItem = parent;
    this->index = index;
    name = QString("Reg%1").arg(GetAddress());
}

int RegistersPackHandler::RegisterHandler::GetAddress()
{
    return (parentItem != nullptr) ? (parentItem->start + index) : -1;
}

void RegistersPackHandler::RegisterHandler::SetData(const qreal &x, const quint16 &y)
{
    parentItem->data[index] = y;
    dataSeries.append(x, y);
}

quint16 RegistersPackHandler::RegisterHandler::GetData()
{
    return (parentItem != nullptr) ? parentItem->data.at(index) : -1;
}
