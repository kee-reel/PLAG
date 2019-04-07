#ifndef MODBUSDEVICESMODEL_H
#define MODBUSDEVICESMODEL_H

#include <QAbstractItemModel>
#include <QBitArray>
#include <QObject>

#include "../../Interfaces/imodbusdatareader.h"

class ModbusDevicesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModbusDevicesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool removeRows(int row, int count, const QModelIndex &parent) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

public:
    void UpdateDevicesList(QList<IModbusDeviceDataManager::IModbusDeviceHandler *> devices);
    QStringListModel *GetDeviceNamesModel();
    IModbusDeviceDataManager::IModbusDeviceHandler *GetDeviceByName(QString deviceName);

private:
    struct DeviceExtraData
    {
        QString name;
        bool enabled;
    };

    QList<IModbusDeviceDataManager::IModbusDeviceHandler *> devices;
    QMap<IModbusDeviceDataManager::IModbusDeviceHandler *, DeviceExtraData> devicesExtraData;
    QStringListModel devicesNamesModel;

    void InsertModelDeviceName(int row, QString uniqueName);
};

#endif // MODBUSDEVICESMODEL_H
