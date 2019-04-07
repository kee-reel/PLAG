#ifndef REGISTERSPACKTABLEMODEL_H
#define REGISTERSPACKTABLEMODEL_H

#include <QAbstractItemModel>
#include <QBitArray>
#include <QObject>

#include "../../Interfaces/imodbusdatareader.h"

#include "registerspackhandler.h"

class RegistersPackTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    RegistersPackTableModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

public slots:
    void AddRegisterPack(IModbusDataReader::RegstersPack pack);
    void ReadRegistersPack(QModbusDataUnit::RegisterType dataType, int startAddress, const QVector<quint16> &data);

signals:
    void updateViewport();

public:
    void SetActiveDevice(IModbusDeviceDataManager::IModbusDeviceHandler *device);
    QList<QLineSeries*> GetDataLineSeries();
    void CleanStoredData();
    void SetStartTime(QDateTime experimentStartTime);

private:
    IModbusDeviceDataManager::IModbusDeviceHandler *activeDevice;
    QMap<IModbusDeviceDataManager::IModbusDeviceHandler *, QList<RegistersPackHandler*> > devicesPacks;
    QList<RegistersPackHandler*> *activePacks;
    QHash<int, RegistersPackHandler*> registerPacksHash;
    QHash<int, QLineSeries*> registersLineSeriesHash;
    quint64 experimentStartTime;

    QString GetRegisterString(QModbusDataUnit::RegisterType type) const;
    QModbusDataUnit::RegisterType GetRegisterType(QString str) const;
    IModbusDataReader::RegstersPack *FindExistedPack(IModbusDataReader::RegstersPack pack);

    // QAbstractItemModel interface
public:
    bool removeRows(int row, int count, const QModelIndex &parent) override;
};

#endif // REGISTERSPACKTABLEMODEL_H
